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
//!  \file dwm_gmk_rgxreplace.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_rgxreplace GNU make extension function
//---------------------------------------------------------------------------

#include <cstring>
#include <regex>
#include <string>

#include "dwm_gmk.h"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_rgxreplace(const char *name, unsigned int argc, char *argv[])
{
  namespace  rgxflags = std::regex_constants;
  
  char  *rc = 0;

  if ((argc == 3) && argv[0] && argv[1] && argv[2]) {
    std::string  rgxstr(argv[0]);
    std::string  fmt(argv[1]);
    std::string  text(argv[2]);
    std::regex   rgx(rgxstr, rgxflags::ECMAScript|rgxflags::optimize);
    std::string  outstr = regex_replace(text, rgx, fmt);
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
