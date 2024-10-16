extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}
  
#include "dwm_gmk.h"

#include <cstring>
#include <filesystem>
#include <string>

extern std::string  g_dwm_gmk_thisdir;

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_thisdir(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (! g_dwm_gmk_thisdir.empty()) {
    rc = gmk_alloc(g_dwm_gmk_thisdir.size() + 1);
    if (rc) {
      rc[g_dwm_gmk_thisdir.size()] = 0;
      strncpy(rc, g_dwm_gmk_thisdir.c_str(), g_dwm_gmk_thisdir.size());
    }
  }
  return rc;
}
