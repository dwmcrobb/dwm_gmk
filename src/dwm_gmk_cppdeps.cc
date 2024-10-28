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
//!  \file dwm_gmk_cppdeps.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_cppdeps GNU make extension function
//---------------------------------------------------------------------------

#include <iostream>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

using namespace std;

//  What do I need as arguments?
//   - deps directory path
//   - object directory path
//   - source file name
//   - compile command
//   - object file extensions (optional, assume .o)

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_cppdeps(const char *name, unsigned int argc, char *argv[])
{
  char  *rule = 0;
  
  if ((argc >= 4) && argv[0] && argv[1] && argv[2] && argv[3]) {
    string  depsdir(argv[0]);
    string  objdir(argv[1]);
    string  srcfile(argv[2]);
    string  cxxcmd(argv[3]);
    vector<string>  obj_exts = { ".o" };
    if (argc >= 5) {
      Dwm::Gmk::ToVector(string(argv[4]), obj_exts);
    }
    string  rulestr(depsdir + "/%_deps: " + srcfile + '\n');
    rulestr += "\t@echo making dependencies for $(dwm_relpwd $<)\n";
    rulestr += "\t@set -e; \\\n";
    rulestr += "\t" + cxxcmd + " $< | \\\n";
    rulestr += "sed 's|\\($*\\).o[ :]*|";
    for (auto ext : obj_exts) {
      rulestr += objdir + "/\\1" + ext;
      rulestr += ' ';
    }
    rulestr += "$(@D)/$(@F) : |g' > $@ ; [ -s $@ ] || \\\n";
    rulestr += "rm -f $@\n";
    rule = Dwm::Gmk::GmkCopy(rulestr);
  }
  return rule;
}

