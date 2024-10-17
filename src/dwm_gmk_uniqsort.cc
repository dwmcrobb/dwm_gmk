extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}

#include <algorithm>
#include <cstring>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_uniqsort(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (argc == 1) {
    std::string_view  sv(argv[0]);
    std::vector<std::string>  v;
    if (Dwm::Gmk::ToVector(sv, v)) {
      std::sort(v.begin(), v.end());
      auto last = std::unique(v.begin(), v.end());
      v.erase(last, v.end());
      std::string  s;
      Dwm::Gmk::ToString(v, s);
      rc = gmk_alloc(s.size() + 1);
      if (rc) {
        rc[s.size()] = 0;
        strncpy(rc, s.c_str(), s.size());
      }
    }
  }
  return rc;
}
