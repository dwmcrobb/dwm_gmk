extern "C" {
  #include "dwm_gmk.h"
}

#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static bool IsFile(const fs::path & p)
{
  bool  rc = false;
  fs::file_status  s = fs::status(p);
  switch (s.type()) {
    case fs::file_type::regular:
    case fs::file_type::block:
    case fs::file_type::character:
    case fs::file_type::fifo:
    case fs::file_type::socket:
      rc = true;
      break;
    default:
      break;
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_relpath(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (argc == 2) {
    if (argv[0] && argv[1]) {
      std::string  base(argv[0]);
      if (IsFile(base)) {
        base = fs::path(base).parent_path().string();
        if (base.empty()) {
          base = "./";
        }
      }
      auto  rel = fs::relative(std::string(argv[1]), base).string();
      if (! rel.empty()) {
        rc = gmk_alloc(rel.size() + 1);
        rc[rel.size()] = '\0';
        strncpy(rc, rel.c_str(), rel.size());
      }
    }
  }
  return rc;
}


  
