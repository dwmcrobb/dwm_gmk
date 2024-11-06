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
static void dwm_gmk_unique_vec(vector<string> & v)
{
  std::sort(v.begin(), v.end());
  auto  endit = std::unique(v.begin(), v.end());
  v.erase(endit, v.end());
  return;
}

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
  vector<string>  objs, shObjs, rmObjs;
  for (const auto & src : srcsv) {
    string  srcStem = fs::path(src).stem().string();
    objs.push_back(objdirabs + "/" + srcStem + ".o");
    shObjs.push_back(objdirabs + "/" + srcStem + ".lo");
    rmObjs.push_back(objdirabs + "/.libs/" + srcStem + ".o");
  }

  string  objsstr;
  dwm_gmk_unique_vec(objs);
  Dwm::Gmk::ToString(objs, objsstr);
  g_myVars.SetVarValueImmediate(ns + ".Objs", objsstr);

  string  shobjsstr;
  dwm_gmk_unique_vec(shObjs);
  Dwm::Gmk::ToString(shObjs, shobjsstr);
  g_myVars.SetVarValueImmediate(ns + ".SharedObjs", shobjsstr);

  string  rmobjsstr;
  dwm_gmk_unique_vec(rmObjs);
  Dwm::Gmk::ToString(rmObjs, rmobjsstr);

  g_myVars.SetVarValueImmediate(ns + ".Clean",
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
  vector<string>  deps;
  for (const auto & src : srcsv) {
    string  srcStem = fs::path(src).stem().string();
    deps.push_back(depsdirabs + "/" + srcStem + "_deps");
  }
  dwm_gmk_unique_vec(deps);

  string  depsstr;
  Dwm::Gmk::ToString(deps, depsstr);
  g_myVars.SetVarValueImmediate(ns + ".Deps", depsstr);

  return;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static void dwm_gmk_set_flex_outs(const std::string & ns,
                                  const std::string & thisdir,
                                  const std::vector<std::string> & srcsv)
{
  namespace  fs = std::filesystem;
  
  vector<string>  flexOuts;
  for (const auto & src : srcsv) {
    string  ex = fs::path(src).extension();
    if (ex == ".lex") {
      string  srcStem = fs::path(src).stem();
      flexOuts.push_back(thisdir + "/" + srcStem + ".cc");
    }
  }
  if (! flexOuts.empty()) {
    string  flexOutsStr;
    Dwm::Gmk::ToString(flexOuts, flexOutsStr);
    g_myVars.SetVarValueImmediate(ns + ".FlexOuts", flexOutsStr);
    g_myVars.SetVarValueImmediate(ns + ".Clean",
                                  g_myVars.GetVarValueString(ns + ".Clean")
                                  + " " + flexOutsStr);
  }
  return;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static void dwm_gmk_set_bison_outs(const std::string & ns,
                                   const std::string & thisdir,
                                   const std::vector<std::string> & srcsv)
{
  namespace  fs = std::filesystem;

  vector<string>  bisonOuts;
  for (const auto & src : srcsv) {
    string  ex = fs::path(src).extension();
    if (ex == ".y") {
      string  srcStem = fs::path(src).stem();
      bisonOuts.push_back(thisdir + "/" + srcStem + ".cc");
      bisonOuts.push_back(thisdir + "/" + srcStem + ".hh");
    }
  }
  if (! bisonOuts.empty()) {
    string  bisonOutsStr;
    Dwm::Gmk::ToString(bisonOuts, bisonOutsStr);
    g_myVars.SetVarValueImmediate(ns + ".BisonOuts", bisonOutsStr);
    g_myVars.SetVarValueImmediate(ns + ".Clean",
                                  g_myVars.GetVarValueString(ns + ".Clean")
                                  + " " + bisonOutsStr);
  }
  return;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_setltlibvars(const char *name, unsigned int argc, char *argv[])
{
  namespace  fs = std::filesystem;
  
  if (argc == 5) {
    string  ns(argv[0]);
    string  lib(argv[1]);
    string  objdir(argv[2]);
    string  depsdir(argv[3]);
    string  srcsrgx(argv[4]);

    string  thisdir = g_mkfileStack.TopDir();
    vector<string>  srcsv;
    Dwm::Gmk::GmkFiles(thisdir, srcsrgx, srcsv);
    string  srcsstr;
    Dwm::Gmk::ToString(srcsv, srcsstr);
    g_myVars.SetVarValueImmediate(ns + ".Srcs", srcsstr);
    
    dwm_gmk_set_objs(ns, thisdir, objdir, srcsv);
    dwm_gmk_set_deps(ns, thisdir, depsdir, srcsv);
    dwm_gmk_set_flex_outs(ns, thisdir, srcsv);
    dwm_gmk_set_bison_outs(ns, thisdir, srcsv);
    
    string  libabs = fs::weakly_canonical(thisdir + "/" + lib);
    g_myVars.SetVarValueImmediate(ns + ".Lib", libabs);
    g_myVars.SetVarValueImmediate(ns + ".Targets", libabs);
    g_myVars.SetVarValueImmediate(ns + ".LtClean", libabs);
  }
  return nullptr;
}
