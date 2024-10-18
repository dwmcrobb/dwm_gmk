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
//!  \file dwm_gmk_thisdir.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_bison GNU make extension function
//---------------------------------------------------------------------------

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
