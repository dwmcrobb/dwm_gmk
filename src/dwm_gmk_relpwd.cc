#include <cstdlib>

#include "dwm_gmk.h"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_relpwd(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (argc == 1) {
    char  *paths[2] = {
      getenv("PWD"),
      argv[0]
    };
    rc = dwm_gmk_relpath("dwm_relpath", 2, paths);
  }
  return rc;
}

