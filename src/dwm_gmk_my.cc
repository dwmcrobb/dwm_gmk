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
//!  \file dwm_gmk_my.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_my GNU make extension function
//---------------------------------------------------------------------------

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>

#include "dwm_gmk.h"
#include "DwmGmkMyVars.hh"
#include "DwmGmkUtils.hh"

using namespace std;

Dwm::Gmk::MyVars  g_myVars;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_myns(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if (argc == 1) {
    if (strlen(argv[0])) {
      char  *ns = gmk_expand(argv[0]);
      if (ns) {
        g_myVars.SetNamespace(ns);
        gmk_floc  floc;
        string  toEval(string("myns := ") + g_myVars.GetNamespaceString());
        gmk_eval(toEval.c_str(), &floc);
      }
    }
    else {
      rc = g_myVars.GetNamespace();
    }
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_my(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if ((argc == 1) && argv[0]) {
    vector<string>  v;
    if (Dwm::Gmk::ToVector(argv[0], v, "\\s+")) {
      if (v.size() == 1) {
        rc = g_myVars.GetVarValue(v[0]);
      }
      else if (v.size() >= 3) {
        g_myVars.SetVarValue(v);
      }
    }
  }
  else if (argc > 1) {
    rc = g_myVars.GetVarValues(argc, argv);
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_myvn(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  string  ns(argv[0]);
  if ((argc == 0) || ns.empty()) {
    rc = g_myVars.GetVarNames();
  }
  else if ((argc == 1) && argv[0]) {
    rc = g_myVars.GetVarNames(argv[0]);
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_myvrgx(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if ((argc == 1) && strlen(argv[0])) {
    string  rcstr = g_myVars.GetVarValuesString(argv[0]);
    if (! rcstr.empty()) {
      rc = Dwm::Gmk::GmkCopy(rcstr);
    }
  }
  return rc;
}
