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
//!  \file dwm_gmk_uniqright.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_uniqright GNU make extension function
//---------------------------------------------------------------------------

#include <algorithm>
#include <set>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_uniqright(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (argc == 1) {
    std::string_view  sv(argv[0]);
    std::vector<std::string>  v;
    if (Dwm::Gmk::ToVector(sv, v)) {
      std::vector<std::string> rv;
      std::set<std::string>  seen;
      for (auto it = v.crbegin(); it != v.crend(); ++it) {
        if (seen.find(*it) == seen.end()) {
          seen.insert(*it);
          rv.push_back(*it);
        }
      }
      std::reverse(rv.begin(), rv.end());
      std::string  s;
      Dwm::Gmk::ToString(rv, s);
      rc = Dwm::Gmk::GmkCopy(s);
    }
  }
  return rc;
}
