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
//!  \file dwm_gmk_relpath.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_relpath GNU make extension function
//---------------------------------------------------------------------------

#include "dwm_gmk.h"

#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>

#include "DwmGmkUtils.hh"

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_relpath(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (argc == 2) {
    if (argv[0] && argv[1]) {
      std::string  base(argv[0]);
      if (Dwm::Gmk::IsFile(base)) {
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


  
