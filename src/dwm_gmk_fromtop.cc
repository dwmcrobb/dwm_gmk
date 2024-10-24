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
//!  \file dwm_gmk_fromtop.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_fromtop GNU make extension function
//---------------------------------------------------------------------------

#include <cstring>
#include <filesystem>
#include <iostream>
#include <stack>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

extern std::stack<std::string> g_thisdirStack;

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_fromtop(const char *name, unsigned int argc, char *argv[])
{
  char  *rel = 0;
  if ((! Dwm::Gmk::Top().empty()) && (! g_thisdirStack.empty())) {
    std::string  toPath = g_thisdirStack.top();
    if (argc == 1) {
      toPath += '/';
      toPath += argv[0];
    }
    std::string  relPath = Dwm::Gmk::RelTop(toPath);
    if (! relPath.empty()) {
      rel = gmk_alloc(relPath.size() + 1);
      if (rel) {
        strncpy(rel, relPath.c_str(), relPath.size());
      }
    }
  }
  return rel;
}
