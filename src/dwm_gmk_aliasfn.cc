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
//!  \file dwm_gmk_aliasfn.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_aliasfn GNU make extension function
//---------------------------------------------------------------------------

extern "C" {
  #include <sys/param.h>
  #include <unistd.h>
}

#include <algorithm>
#include <iostream>
#include <cstring>
#include <map>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  Map from an alias to a built-in fuction.
//----------------------------------------------------------------------------
std::map<std::string,std::string>  g_builtin_aliases;

//----------------------------------------------------------------------------
//!  Built-in functions that we can alias.
//----------------------------------------------------------------------------
static const std::vector<dwm_gmk_bi_fn_entry>  dwm_gmk_builtin_funcs = {
  { "subst",      3, 3, GMK_FUNC_DEFAULT },
  { "patsubst",   3, 3, GMK_FUNC_DEFAULT },
  { "strip",      1, 1, GMK_FUNC_DEFAULT },
  { "findstring", 2, 2, GMK_FUNC_DEFAULT },
  { "filter",     2, 2, GMK_FUNC_DEFAULT },
  { "filter-out", 2, 2, GMK_FUNC_DEFAULT },
  { "sort",       1, 1, GMK_FUNC_DEFAULT },
  { "word",       2, 2, GMK_FUNC_DEFAULT },
  { "wordlist",   3, 3, GMK_FUNC_DEFAULT },
  { "words",      1, 1, GMK_FUNC_DEFAULT },
  { "firstword",  1, 1, GMK_FUNC_DEFAULT },
  { "lastword",   1, 1, GMK_FUNC_DEFAULT },
  { "dir",        1, 1, GMK_FUNC_DEFAULT },
  { "notdir",     1, 1, GMK_FUNC_DEFAULT },
  { "suffix",     1, 1, GMK_FUNC_DEFAULT },
  { "basename",   1, 1, GMK_FUNC_DEFAULT },
  { "addsuffix",  2, 2, GMK_FUNC_DEFAULT },
  { "addprefix",  2, 2, GMK_FUNC_DEFAULT },
  { "join",       2, 2, GMK_FUNC_DEFAULT },
  { "wildcard",   1, 1, GMK_FUNC_DEFAULT },
  { "realpath",   1, 1, GMK_FUNC_DEFAULT },
  { "abspath",    1, 1, GMK_FUNC_DEFAULT },
  { "if",         2, 3, GMK_FUNC_DEFAULT },
  { "or",         1, 0, GMK_FUNC_DEFAULT },
  { "and",        1, 0, GMK_FUNC_DEFAULT },
  { "intcmp",     2, 5, GMK_FUNC_DEFAULT },
  { "foreach",    3, 3, GMK_FUNC_DEFAULT },
  { "file",       2, 3, GMK_FUNC_DEFAULT },
  { "call",       1, 0, GMK_FUNC_DEFAULT },
  { "value",      1, 1, GMK_FUNC_DEFAULT },
  { "origin",     1, 1, GMK_FUNC_DEFAULT },
  { "flavor",     1, 1, GMK_FUNC_DEFAULT },
  { "error",      1, 1, GMK_FUNC_DEFAULT },
  { "warning",    1, 1, GMK_FUNC_DEFAULT },
  { "info",       1, 1, GMK_FUNC_DEFAULT },
  { "shell",      1, 1, GMK_FUNC_DEFAULT },
};
     
//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_aliasfn(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if (argc == 2 && strlen(argv[0]) && strlen(argv[1])) {
    auto  it = std::find_if(dwm_gmk_function_entries.begin(),
                            dwm_gmk_function_entries.end(),
                            [&] (const auto & entry)
                            { return (strcmp(argv[1], entry.name) == 0); });
    if (it != dwm_gmk_function_entries.end()) {
      gmk_add_function(argv[0], it->fn, it->min_args,
                       it->max_args, it->flags);
    }
    else {
      auto bfit = std::find_if(dwm_gmk_builtin_funcs.begin(),
                               dwm_gmk_builtin_funcs.end(),
                               [&] (const auto & entry)
                               { return (strcmp(argv[1], entry.name) == 0); });
      if (bfit != dwm_gmk_builtin_funcs.end()) {
        gmk_add_function(argv[0], dwm_gmk_call_builtin, bfit->min_args,
                         bfit->max_args, bfit->flags);
        g_builtin_aliases[argv[0]] = argv[1];
      }
    }
  }
  return rc;
}
