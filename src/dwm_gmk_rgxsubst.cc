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
//!  \file dwm_gmk_rgxsubst.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_rgxsubst GNU make extension function
//---------------------------------------------------------------------------

#include <regex>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_rgxsubst(const char *name, unsigned int argc, char *argv[])
{
  namespace  rgxflags = std::regex_constants;
  
  char  *rc = nullptr;

  if ((argc == 3) && argv[0] && argv[1] && argv[2]) {
    std::string  rgxstr(argv[0]);
    std::string  fmt(argv[1]);
    std::string  s(argv[2]);

    std::vector<std::string>  words;
    if (Dwm::Gmk::ToVector(s, words)) {
      std::string  outstr;
      std::regex   rgx(rgxstr, rgxflags::ECMAScript|rgxflags::optimize);
      auto  word = words.cbegin();
      outstr += regex_replace(*word, rgx, fmt);
      ++word;
      for (; word != words.end(); ++word) {
        outstr += ' ';
        outstr += regex_replace(*word, rgx, fmt);
      }
      if (! outstr.empty()) {
        rc = Dwm::Gmk::GmkCopy(outstr);
      }
    }
  }
  return rc;
}
