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
//!  \file dwm_gmk_totop.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_totop GNU make extension function
//---------------------------------------------------------------------------

#include "dwm_gmk.h"

#include <cstring>
#include <filesystem>
#include <string>

#include "DwmGmkUtils.hh"

extern std::string  g_dwm_gmk_thisdir_abs;
extern std::string  g_dwm_gmk_topdir_abs;

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_totop(const char *name, unsigned int argc, char *argv[])         
{
  char  *rel = 0;
  if ((! g_dwm_gmk_topdir_abs.empty()) && (! g_dwm_gmk_thisdir_abs.empty())) {
    std::string  fromPath = g_dwm_gmk_thisdir_abs;
    if (argc == 1) {
      fromPath += '/';
      fromPath += argv[0];
    }
    fromPath = fs::weakly_canonical(fromPath);
    if (Dwm::Gmk::IsFile(fromPath)) {
      fromPath = fs::path(fromPath).parent_path();
    }
    std::string  relPath = fs::proximate(g_dwm_gmk_topdir_abs,fromPath);
    if (! relPath.empty()) {
      rel = gmk_alloc(relPath.size() + 1);
      if (rel) {
        strncpy(rel, relPath.c_str(), relPath.size());
      }
    }
  }
  return rel;
}
