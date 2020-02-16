#ifndef CSAPI_CSCAN_H
#define CSAPI_CSCAN_H

#include "postgres.h"
#include "optimizer/pathnode.h"

void init_custom_scan(void);
void add_custom_path(PlannerInfo *root, RelOptInfo *rel, Index rti, RangeTblEntry *rte);

#endif  //CSAPI_CSCAN_H