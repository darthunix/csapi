#ifndef CSAPI_HOOKS_H
#define CSAPI_HOOKS_H

#include "postgres.h"
#include "optimizer/paths.h"


set_rel_pathlist_hook_type prev_set_rel_pathlist_hook_type;
void csapi_rel_pathlist_hook (PlannerInfo *root, RelOptInfo *rel, Index rti, RangeTblEntry *rte);

#endif  //CSAPI_HOOKS_H