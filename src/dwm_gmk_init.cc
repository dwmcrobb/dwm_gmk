//===========================================================================
//  Copyright (c) Daniel W. McRobb 2024
//  All rights reserved.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//===========================================================================

//---------------------------------------------------------------------------
//!  \file dwm_gmk_init.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_bison GNU make extension function
//---------------------------------------------------------------------------

extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}
  
#include "dwm_gmk.h"

#include <filesystem>
#include <string>

std::string  g_dwm_gmk_thisdir;
std::string  g_dwm_gmk_thisdir_abs;
std::string  g_dwm_gmk_pwd;

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
    g_dwm_gmk_thisdir_abs = mkfile.parent_path();
    char  cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd))) {
      g_dwm_gmk_pwd = cwd;
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
