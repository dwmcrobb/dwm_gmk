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
//!  \file dwm_gmk_subdirs.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_subdirs GNU make extension function
//---------------------------------------------------------------------------

#include <filesystem>
#include <regex>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_subdirs(const char *name, unsigned int argc, char *argv[])
{
  namespace  rgxflags = std::regex_constants;
  
  char  *rc = nullptr;
  std::string  dirPath, rgxstr;

  if ((argc >= 1) && argv[0]) {
    dirPath = argv[0];
  }
  if ((argc == 2) && argv[1]) {
    rgxstr = argv[1];
  }

  if (dirPath.empty()) {
    dirPath = dwm_gmk_thisdir("dwm_thisdir", 0, 0);
  }
  if (rgxstr.empty()) {
    rgxstr = ".+";
  }

  std::regex   rgx(rgxstr, rgxflags::ECMAScript|rgxflags::optimize);
  std::smatch  sm;
  std::string  dirsstr;

  try {
    std::string  spc;
    for (auto const & dirEntry : fs::directory_iterator{dirPath}) {
      if (dirEntry.is_directory()) {
        std::string  dirName = dirEntry.path().filename().string();
        if (regex_match(dirName, sm, rgx)) {
          dirsstr += spc + dirName;
          spc = " ";
        }
      }
    }
  }
  catch (...) {
  }
  
  if (! dirsstr.empty()) {
    rc = Dwm::Gmk::GmkCopy(dirsstr);
  }
  return rc;
}
