extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}
  
#include "dwm_gmk.h"

#include <cstring>
#include <filesystem>
#include <regex>
#include <string>

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_dirfiles(const char *name, unsigned int argc, char *argv[])
{
  namespace  rgxflags = std::regex_constants;
  
  char  *rc = 0;
  std::string  dirPath, rgxstr;
  
  if (argc == 2) {
    dirPath = argv[0];
    rgxstr = argv[1];
  }

  if (dirPath.empty()) {
    dirPath = dwm_gmk_thisdir("dwm_thisdir", 0, 0);
  }
  if (rgxstr.empty()) {
    rgxstr = ".+";
  }

  std::regex   rgx(rgxstr, rgxflags::ECMAScript|rgxflags::optimize);
  std::smatch  sm;
  std::string  filesstr;
  for (auto const & dirEntry : fs::directory_iterator{dirPath}) {
    if (! dirEntry.is_directory()) {
      std::string  fileName = dirEntry.path().filename().string();
      if (regex_match(fileName, sm, rgx)) {
        filesstr += fileName + ' ';
      }
    }
  }
  if (! filesstr.empty()) {
    rc = gmk_alloc(filesstr.size());
    rc[filesstr.size() - 1] = '\0';
    if (rc) {
      strncpy(rc, filesstr.c_str(), filesstr.size() - 1);
    }
  }
  return rc;
}
