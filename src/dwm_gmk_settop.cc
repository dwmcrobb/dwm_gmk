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
//!  \file dwm_gmk_settop.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_settop GNU make extension function
//---------------------------------------------------------------------------

#include "dwm_gmk.h"

#include <filesystem>
#include <iostream>
#include <string>

std::string  g_dwm_gmk_topdir_abs;

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_settop(const char *name, unsigned int argc, char *argv[])
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
    g_dwm_gmk_topdir_abs = mkfile.parent_path();
    gmk_free(mkfileList);
  }
  if (rc) {
    gmk_free(rc);
  }
  return 0;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_top(const char *name, unsigned int argc, char *argv[])         
{
  char  *top = 0;
  if (! g_dwm_gmk_topdir_abs.empty()) {
    top = gmk_alloc(g_dwm_gmk_topdir_abs.size() + 1);
    if (top) {
      strncpy(top, g_dwm_gmk_topdir_abs.c_str(), g_dwm_gmk_topdir_abs.size());
    }
  }
  return top;
}
