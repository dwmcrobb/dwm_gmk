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
//!  \file dwm_gmk_rgxmatch.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_rgxmatch GNU make extension function
//---------------------------------------------------------------------------

#include <cstring>
#include <filesystem>
#include <regex>
#include <string>

#include "dwm_gmk.h"

namespace fs = std::filesystem;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_rgxmatch(const char *name, unsigned int argc, char *argv[])
{
  namespace  rgxflags = std::regex_constants;
  
  char  *rc = 0;

  if ((argc == 2) && argv[0] && argv[1]) {
    std::string  s(argv[0]);
    std::string  rgxstr(argv[1]);
    std::regex   rgx(rgxstr, rgxflags::ECMAScript|rgxflags::optimize);
    std::smatch  sm;
    std::string  outstr;
    if (regex_match(s, sm, rgx)) {
      auto  it = sm.cbegin();
      outstr += it->str();
      ++it;
      for (; it != sm.end(); ++it) {
        outstr += ' ';
        outstr += it->str();
      }
    }
    if (! outstr.empty()) {
      rc = gmk_alloc(outstr.size() + 1);
      if (rc) {
        rc[outstr.size()] = 0;
        strncpy(rc, outstr.c_str(), outstr.size());
      }
    }
  }
  return rc;
}
