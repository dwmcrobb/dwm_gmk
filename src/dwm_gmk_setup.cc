#include "dwm_gmk.h"

extern "C" {
    int plugin_is_GPL_compatible = 1;
}

//---------------------------------------------------------------------------
//!  
//---------------------------------------------------------------------------
int dwm_gmk_setup(const gmk_floc *floc)
{
    gmk_add_function("dwm_relpath", dwm_gmk_relpath, 2, 2, 0);
    gmk_add_function("dwm_thisdir", dwm_gmk_thisdir, 0, 0, 0);
    gmk_add_function("dwm_dirfiles", dwm_gmk_dirfiles, 2, 2, 0);
    return 1;
}

