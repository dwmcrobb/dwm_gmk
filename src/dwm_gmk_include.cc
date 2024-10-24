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
//!  \file dwm_gmk_include.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_include GNU make extension function
//---------------------------------------------------------------------------

extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
#include <stack>
#include <utility>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

using namespace std;
namespace fs = std::filesystem;

extern stack<string>  g_thisdirStack;
extern stack<string>  g_thisfileStack;
static set<string>    g_alreadyIncluded;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static string RelToPwd(const string & p)
{
  string   relpath(p);
  string   pwdstr;
  char    *pwd = getenv("PWD");
  if (pwd) {
    pwdstr = pwd;
    relpath = fs::relative(p, pwdstr);
  }
  return relpath;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_include(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (argc == 1) {
    vector<string>  makefiles;
    Dwm::Gmk::GetMakefilesList(makefiles);
    string  includedFromDirAbs = g_thisdirStack.top();
    vector<string>  includeFiles;
    Dwm::Gmk::ToVector(string_view(argv[0]), includeFiles);
    for (auto includeArg : includeFiles) {
      string  includePathAbs;
      if (includeArg.at(0) != '/') {
        includePathAbs = includedFromDirAbs + '/' + includeArg;
      }
      else {
        includePathAbs = includeArg;
      }
      includePathAbs = fs::weakly_canonical(includePathAbs);
      if (g_alreadyIncluded.find(includePathAbs) == g_alreadyIncluded.end()) {
        string  includePathDir = fs::path(includePathAbs).parent_path();
        cout << "including " << RelToPwd(includePathAbs) << " from "
             << RelToPwd(g_thisfileStack.top()) << '\n';
        g_thisdirStack.push(includePathDir);
        g_thisfileStack.push(includePathAbs);
        string  includeDirective = string("include ") + includePathAbs;
        gmk_floc floc = { __FILE__, __LINE__ };
        gmk_eval(includeDirective.c_str(), &floc);
        g_thisdirStack.pop();
        g_thisfileStack.pop();
        g_alreadyIncluded.insert(includePathAbs);
      }
      else {
        cout << RelToPwd(includePathAbs) << " already included\n";
      }
      cout.flush();
    }
  }
  return rc;
}

