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
//!  \file dwm_gmk_vrgx.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_vrgx GNU make extension function
//---------------------------------------------------------------------------

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <regex>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

using namespace std;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_vrgx(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if (argc == 1) {
    if (strlen(argv[0])) {
      vector<string>  varNames;
      char  *gmk_VARIABLES = gmk_expand("$(.VARIABLES)");
      if (gmk_VARIABLES) {
        Dwm::Gmk::ToVector(string_view(gmk_VARIABLES), varNames);
        gmk_free(gmk_VARIABLES);
      }
      if (! varNames.empty()) {
        string  rcstr, spc;
        regex   rgx(argv[0], regex::ECMAScript|regex::optimize);
        smatch  sm;
        for (const auto & varName : varNames) {
          if (regex_match(varName, sm, rgx)) {
            char  *varVal = gmk_expand(string("$(" + varName + ")").c_str());
            if (varVal && strlen(varVal)) {
              rcstr += spc + varVal;
              spc = " ";
              gmk_free(varVal);
            }
          }
        }
        if (! rcstr.empty()) {
          rc = Dwm::Gmk::GmkCopy(rcstr);
        }
      }
    }
  }
  return rc;
}
