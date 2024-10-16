extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}
  
#include "dwm_gmk.h"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_thisdir(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  char  *mkfileList = gmk_expand("$(MAKEFILE_LIST)");
  if (mkfileList) {
    std::string  s(mkfileList);
    size_t  idx = s.find_last_of(' ');
    if (idx == std::string::npos) {
      idx = 0;
    }
    char  cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd))) {
      fs::path  mkfile = fs::weakly_canonical(s.substr(idx));
      fs::path  mkfileDir = mkfile.parent_path();
      std::string  mkfileDirStr = mkfileDir.string();
      char *paths[2] = { cwd, mkfileDirStr.data() };
      rc = dwm_gmk_relpath("dwm_relpath", 2, paths);
    }
    gmk_free(mkfileList);
  }
  return rc;
}
