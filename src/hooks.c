#include "include/hooks.h"
#include "include/cscan.h"


void csapi_rel_pathlist_hook (PlannerInfo *root, RelOptInfo *rel, Index rti, RangeTblEntry *rte)
{
    if(prev_set_rel_pathlist_hook_type)
        prev_set_rel_pathlist_hook_type(root, rel, rti, rte);

    add_custom_path(root, rel, rti, rte);
}
