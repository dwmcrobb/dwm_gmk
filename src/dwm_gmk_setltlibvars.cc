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
//!  \file dwm_gmk_setltlibvars.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk rotate GNU make extension functions
//---------------------------------------------------------------------------

#include <algorithm>
// #include <cstring>
#include <filesystem>
#include <iostream>
#include <regex>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"
#include "DwmGmkMkfileStack.hh"
#include "DwmGmkMyVars.hh"

extern Dwm::Gmk::MkfileStack  g_mkfileStack;
extern Dwm::Gmk::MyVars       g_myVars;

using namespace std;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static void dwm_gmk_set_objs(const std::string & ns, const string & thisdir,
                             const string & objdir,
                             const vector<string> & srcsv)
{
  namespace  fs = std::filesystem;
  string  objdirabs = fs::weakly_canonical(thisdir + "/" + objdir);
  g_myVars.SetVarValueImmediate(ns + ".ObjDir", objdirabs);
  regex   rgx("(.+)\\.(cc|y|lex|ll)$", regex::ECMAScript | regex::optimize);
  vector<string>  objs;
  vector<string>  sharedObjs;
  vector<string>  rmObjs;
  for (const auto & src : srcsv) {
    objs.push_back(regex_replace(src, rgx, objdirabs + "/$1.o"));
    sharedObjs.push_back(regex_replace(src, rgx, objdirabs + "/$1.lo"));
    rmObjs.push_back(regex_replace(src, rgx, objdirabs + "/.libs/$1.o"));
  }
  std::sort(objs.begin(), objs.end());
  auto  endobj = std::unique(objs.begin(), objs.end());
  objs.erase(endobj, objs.end());

  string  objsstr;
  Dwm::Gmk::ToString(objs, objsstr);
  g_myVars.SetVarValueImmediate(ns + ".Objs", objsstr);
  
  std::sort(sharedObjs.begin(), sharedObjs.end());
  auto  endshobj = std::unique(sharedObjs.begin(), sharedObjs.end());
  sharedObjs.erase(endshobj, sharedObjs.end());

  string  shobjsstr;
  Dwm::Gmk::ToString(sharedObjs, shobjsstr);
  g_myVars.SetVarValueImmediate(ns + ".SharedObjs", shobjsstr);

  std::sort(rmObjs.begin(), rmObjs.end());
  auto  endrmobj = std::unique(rmObjs.begin(), rmObjs.end());
  rmObjs.erase(endrmobj, rmObjs.end());
  
  string  rmobjsstr;
  Dwm::Gmk::ToString(rmObjs, rmobjsstr);
  g_myVars.SetVarValueImmediate(ns + ".RmTargets",
                                objsstr + " " + shobjsstr + " " + rmobjsstr);
  return;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static void dwm_gmk_set_deps(const std::string & ns, const string & thisdir,
                             const string & depsdir,
                             const vector<string> & srcsv)
{
  namespace  fs = std::filesystem;
  string  depsdirabs = fs::weakly_canonical(thisdir + "/" + depsdir);
  g_myVars.SetVarValueImmediate(ns + ".DepsDir", depsdirabs);
  regex   rgx("(.+)\\.(cc|y|lex|ll)$", regex::ECMAScript | regex::optimize);
  vector<string>  deps;
  for (const auto & src : srcsv) {
    deps.push_back(regex_replace(src, rgx, depsdirabs + "/$1_deps"));
  }
  std::sort(deps.begin(), deps.end());
  auto  enddep = std::unique(deps.begin(), deps.end());
  deps.erase(enddep, deps.end());

  string  depsstr;
  Dwm::Gmk::ToString(deps, depsstr);
  g_myVars.SetVarValueImmediate(ns + ".Deps", depsstr);

  return;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_setltlibvars(const char *name, unsigned int argc, char *argv[])
{
  namespace  fs = std::filesystem;
  
  if (argc == 6) {
    string  ns(argv[0]);
    string  libdir(argv[1]);
    string  lib(argv[2]);
    string  objdir(argv[3]);
    string  depsdir(argv[4]);
    string  srcs(argv[5]);

    vector<string>  srcsv;
    Dwm::Gmk::ToVector(srcs, srcsv);
    string  thisdir = g_mkfileStack.TopDir();
    dwm_gmk_set_objs(ns, thisdir, objdir, srcsv);
    dwm_gmk_set_deps(ns, thisdir, depsdir, srcsv);

    string  libdirabs = fs::weakly_canonical(thisdir + "/" + libdir);
    g_myVars.SetVarValueImmediate(ns + ".Lib", libdirabs + "/" + lib);
    g_myVars.SetVarValueImmediate(ns + ".Targets", libdirabs + "/" + lib);
    g_myVars.SetVarValueImmediate(ns + ".LtRmTargets",
                                  libdirabs + "/" + lib);
  }
  return nullptr;
}
