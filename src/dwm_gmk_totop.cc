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

#include <filesystem>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"
#include "DwmGmkMkfileStack.hh"

extern Dwm::Gmk::MkfileStack  g_mkfileStack;

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_totop(const char *name, unsigned int argc, char *argv[])         
{
  char  *rel = nullptr;
  std::string  thisdir = g_mkfileStack.TopDir();
  if ((! Dwm::Gmk::Top().empty()) && (! thisdir.empty())) {
    std::string  fromPath = thisdir;
    if (argc == 1) {
      fromPath += '/';
      fromPath += argv[0];
    }
    fromPath = fs::weakly_canonical(fromPath);
    if (Dwm::Gmk::IsFile(fromPath)) {
      fromPath = fs::path(fromPath).parent_path();
    }
    std::string  relPath = fs::proximate(Dwm::Gmk::Top(), fromPath);
    if (! relPath.empty()) {
      rel = Dwm::Gmk::GmkCopy(relPath);
    }
  }
  return rel;
}
