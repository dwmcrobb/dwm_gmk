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
#include "DwmGmkUtils.hh"

#include <filesystem>
#include <iostream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_settop(const char *name, unsigned int argc, char *argv[])
{
  vector<string>  makefiles;
  if (Dwm::Gmk::GetMakefilesList(makefiles)) {
    fs::path  mkfile = fs::weakly_canonical(makefiles.back());
    Dwm::Gmk::SetTop(mkfile.parent_path());
    gmk_eval(std::string("TOP := " + Dwm::Gmk::Top()).c_str(), nullptr);
  }
  return 0;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_top(const char *name, unsigned int argc, char *argv[])         
{
  char  *top = 0;
  std::string  topstr = Dwm::Gmk::Top();
  if (! topstr.empty()) {
    top = gmk_alloc(topstr.size() + 1);
    if (top) {
      strncpy(top, topstr.c_str(), topstr.size());
    }
  }
  return top;
}
