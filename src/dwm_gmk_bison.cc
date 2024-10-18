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
//!  \file dwm_gmk_bison.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_bison GNU make extension function
//---------------------------------------------------------------------------

#include <iostream>
#include <string>

#include "dwm_gmk.h"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_bison(const char *name, unsigned int argc, char *argv[])
{
  using namespace std;
  
  if ((argc == 1) && argv[0]) {
    std::string  rule;
    std::string  _bison_targets = "$(patsubst %.y,%.cc," + string(argv[0])
      + ") $(patsubst %.y,%.hh," + string(argv[0]) + ')';
    char  *tmp = gmk_expand(_bison_targets.c_str());
    if (! tmp) {
      cerr << "Failed to expand " << _bison_targets << '\n';
      return 0;
    }
    _bison_targets = tmp;
    gmk_free(tmp);
    rule += "BISONTARGETS += " + _bison_targets + "\n";
    rule += _bison_targets + " &: " + string(argv[0]) + '\n';
    string  outtarget("$(patsubst %.y,%.cc,");
    outtarget += string(argv[0]) + ')';
    tmp = gmk_expand(outtarget.c_str());
    if (! tmp) {
      cerr << "Failed to expand " << outtarget << '\n';
      return 0;
    }
    outtarget = tmp;
    gmk_free(tmp);
    rule += "\tbison -d -o" + outtarget + " $<\n";
    gmk_floc floc = { __FILE__, __LINE__ };
    gmk_eval(rule.c_str(), &floc);
  }
  return 0;
}

