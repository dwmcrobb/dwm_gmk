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
#include "DwmGmkMkfileStack.hh"

using namespace std;
namespace fs = std::filesystem;

extern Dwm::Gmk::MkfileStack  g_mkfileStack;
static set<string>            g_alreadyIncluded;

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
  char            *rc = nullptr;
  bool             verbose = false;
  vector<string>   includeFiles;
  if (argc == 2) {
    if (strcmp(argv[0], "verbose") == 0) {
      verbose = true;
    }
    Dwm::Gmk::ToVector(string_view(argv[1]), includeFiles);
  }
  else if (argc == 1) {
    Dwm::Gmk::ToVector(string_view(argv[0]), includeFiles);
  }
  
  if (argc >= 1) {
    string  includedFromDirAbs = g_mkfileStack.TopDir();
    for (auto includeFile : includeFiles) {
      string  includeFileAbs;
      if (includeFile.at(0) != '/') {
        includeFileAbs = includedFromDirAbs + '/' + includeFile;
      }
      else {
        includeFileAbs = includeFile;
      }
      includeFileAbs = fs::weakly_canonical(includeFileAbs);
      string  includePathDir = fs::path(includeFileAbs).parent_path();
      if (verbose) {
        cout << "including " << RelToPwd(includeFileAbs) << " from "
             << RelToPwd(g_mkfileStack.TopFile()) << '\n';
        cout.flush();
      }
      g_mkfileStack.Push(includeFileAbs);
      string  includeDirective = string("include ") + includeFileAbs;
      gmk_floc floc = { __FILE__, __LINE__ };
      gmk_eval(includeDirective.c_str(), &floc);
      g_mkfileStack.Pop();
      g_alreadyIncluded.insert(includeFileAbs);
    }
  }
  return rc;
}

