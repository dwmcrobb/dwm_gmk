extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}
  
#include "dwm_gmk.h"

#include <filesystem>
#include <iostream>
#include <string>

std::string  g_dwm_gmk_thisdir;

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_init(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  char  *mkfileList = gmk_expand("$(MAKEFILE_LIST)");
  if (mkfileList) {
    std::string  s(mkfileList);
    fs::path  mkfile;
    size_t  idx = s.find_last_of(' ');
    if (idx == std::string::npos) {
      mkfile = fs::weakly_canonical(s);
    }
    else {
      mkfile = fs::weakly_canonical(s.substr(idx+1));
    }
    char  cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd))) {
      fs::path  mkfileDir = mkfile.parent_path();
      std::string  mkfileDirStr = mkfileDir.string();
      char *paths[2] = { cwd, mkfileDirStr.data() };
      rc = dwm_gmk_relpath("dwm_relpath", 2, paths);
      g_dwm_gmk_thisdir = rc;
    }
    gmk_free(mkfileList);
  }
  if (rc) {
    gmk_free(rc);
  }
  return 0;
}
