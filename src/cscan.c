#include "include/cscan.h"
#include "nodes/extensible.h"
#include "optimizer/cost.h"


static CustomPathMethods cs_path_methods;
static CustomScanMethods cs_plan_methods;
static CustomExecMethods cs_exec_methods;


/* Construct a new custom plan node from a custom path */
static Plan *cs_create_plan(PlannerInfo *root, RelOptInfo *rel, CustomPath *best_path, List *tlist, List *clauses, List *custom_plans)
{
    CustomScan *cscan;
    cscan = makeNode(CustomScan);
    cscan->scan.plan.targetlist = tlist;
    cscan->scan.plan.qual = clauses;
    cscan->scan.plan.lefttree = NULL;
    cscan->scan.plan.righttree = NULL;
    cscan->scan.scanrelid = rel->relid;
    cscan->flags = best_path->flags;
    cscan->custom_plans = NIL;
    cscan->custom_scan_tlist = NIL; /* TODO: change to vectorized tuple list on next iteration */
    cscan->methods = &cs_plan_methods;
    return &cscan->scan.plan;
}


static Node *cs_create_scan_state(CustomScan *cscan)
{
    CustomScanState *css = MemoryContextAllocZero(CurTransactionContext, sizeof(CustomScanState));
    NodeSetTag(css, T_CustomScanState);
    if (cscan->methods == &cs_plan_methods)
    {
        css->methods = &cs_exec_methods;
    }
    else
    {
        elog(ERROR, "WTF?! Unexpected CustomPlanMethod");
    }
    return (Node *) css;
}


void add_custom_path(PlannerInfo *root, RelOptInfo *rel, Index rti, RangeTblEntry *rte)
{
    CustomPath *cpath;
    cpath = makeNode(CustomPath);
    cpath->path.type = T_CustomPath;
    cpath->path.pathtype = T_CustomScan;
    cpath->path.parent = rel;
    cpath->path.param_info = get_baserel_parampathinfo(root, rel, rel->lateral_relids);
    cpath->path.pathkeys = NIL;  /* our custom scan returns unsorted results */
    cpath->path.parallel_aware = false;
    cpath->path.parallel_safe = rel->consider_parallel;
    cpath->path.parallel_workers = 0;
    // TODO: inspect internal of a pathnode->path.pathtarget for a custom output path (can it be  used for vectorized output?)
    cost_seqscan(&cpath->path, root, rel, cpath->path.param_info);
    cpath->methods = &cs_path_methods;

    add_path(rel, &cpath->path);
}


void init_custom_scan(void)
{
    memset(&cs_path_methods, 0, sizeof(cs_path_methods));
    cs_path_methods.CustomName = "CustomScan";
    cs_path_methods.PlanCustomPath = &cs_create_plan;

    memset(&cs_plan_methods, 0, sizeof(cs_plan_methods));
    cs_plan_methods.CustomName = "CustomScan";
    cs_plan_methods.CreateCustomScanState = &cs_create_scan_state;
    RegisterCustomScanMethods(&cs_plan_methods);

    // TODO: init cs_exec_methods structure
}