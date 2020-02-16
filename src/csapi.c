#include "postgres.h"
#include "fmgr.h"
#include "miscadmin.h"
#include "optimizer/paths.h"
#include "include/hooks.h"


#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif


extern void _PG_init(void);
extern void _PG_fini(void);


void _PG_init(void)
{
    if (!process_shared_preload_libraries_in_progress)
        ereport(
            ERROR,
            (
                errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
                errmsg("csapi must be loaded via shared_preload_libraries")
            )
        );

    prev_set_rel_pathlist_hook_type = set_rel_pathlist_hook;
    set_rel_pathlist_hook = csapi_rel_pathlist_hook;
}


void _PG_fini(void)
{
    set_rel_pathlist_hook = prev_set_rel_pathlist_hook_type;
}
