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
//!  \file dwm_gmk_uniqleft.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_uniqleft GNU make extension function
//---------------------------------------------------------------------------

#include <set>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_uniqleft(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if (argc == 1) {
    std::string_view  sv(argv[0]);
    std::vector<std::string>  v;
    if (Dwm::Gmk::ToVector(sv, v)) {
      std::vector<std::string> rv;
      std::set<std::string>  seen;
      for (const auto & word : v) {
        if (seen.find(word) == seen.end()) {
          seen.insert(word);
          rv.push_back(word);
        }
      }
      std::string  s;
      Dwm::Gmk::ToString(rv, s);
      rc = Dwm::Gmk::GmkCopy(s);
    }
  }
  return rc;
}
