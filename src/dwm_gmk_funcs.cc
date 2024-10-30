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
//!  \file dwm_gmk_funcs.cc
//!  \author Daniel W. McRobb
//!  \brief GNU make extension support infrastructure
//---------------------------------------------------------------------------
#include <iostream>
#include <map>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
std::vector<dwm_gmk_fn_entry>  dwm_gmk_function_entries = {
  { "dwm_aliasfn",    dwm_gmk_aliasfn,    2, 2, GMK_FUNC_DEFAULT  },
  { "dwm_bison",      dwm_gmk_bison,      1, 0, GMK_FUNC_DEFAULT  },
  { "dwm_cppdeps",    dwm_gmk_cppdeps,    4, 5, GMK_FUNC_DEFAULT  },
  { "dwm_curpath",    dwm_gmk_curpath,    0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_cwd",        dwm_gmk_curpath,    0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_files",      dwm_gmk_files,      0, 2, GMK_FUNC_DEFAULT  },
  { "dwm_flex",       dwm_gmk_flex,       1, 0, GMK_FUNC_DEFAULT  },
  { "dwm_include",    dwm_gmk_include,    1, 2, GMK_FUNC_DEFAULT  },
  { "dwm_my",         dwm_gmk_my,         1, 1, GMK_FUNC_NOEXPAND },
  { "dwm_myns",       dwm_gmk_myns,       0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_myvn",       dwm_gmk_myvn,       0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_push",       dwm_gmk_push,       0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_popf",       dwm_gmk_popf,       1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_popb",       dwm_gmk_popb,       1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_pwd",        dwm_gmk_pwd,        0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_relpath",    dwm_gmk_relpath,    2, 2, GMK_FUNC_DEFAULT  },
  { "dwm_relpwd",     dwm_gmk_relpwd,     1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_reverse",    dwm_gmk_reverse,    1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_rgxmatch",   dwm_gmk_rgxmatch,   2, 2, GMK_FUNC_DEFAULT  },
  { "dwm_rgxreplace", dwm_gmk_rgxreplace, 3, 3, GMK_FUNC_DEFAULT  },
  { "dwm_rgxsearch",  dwm_gmk_rgxsearch,  2, 2, GMK_FUNC_DEFAULT  },
  { "dwm_rgxsubst",   dwm_gmk_rgxsubst,   3, 3, GMK_FUNC_DEFAULT  },
  { "dwm_rotl",       dwm_gmk_rotl,       1, 2, GMK_FUNC_DEFAULT  },
  { "dwm_rotr",       dwm_gmk_rotr,       1, 2, GMK_FUNC_DEFAULT  },
  { "dwm_sort",       dwm_gmk_sort,       1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_subdirs",    dwm_gmk_subdirs,    0, 2, GMK_FUNC_DEFAULT  },
  { "dwm_thisdir",    dwm_gmk_thisdir,    0, 1, GMK_FUNC_DEFAULT  },
  { "dwm_uniqleft",   dwm_gmk_uniqleft,   1, 1, GMK_FUNC_DEFAULT  },
  { "dwm_uniqright",  dwm_gmk_uniqright,  1, 1, GMK_FUNC_DEFAULT  }
};

//----------------------------------------------------------------------------
//!  Map from an alias to a built-in.
//----------------------------------------------------------------------------
extern std::map<std::string,std::string>  g_builtin_aliases;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_call_builtin(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  auto  it = g_builtin_aliases.find(name);
  if (it != g_builtin_aliases.end()) {
    std::string  ev("$(" + it->second);
    ev += ' ';
    unsigned int  i = 0;
    ev += argv[i++];
    for ( ; i < argc; ++i) {
      ev += ',';
      ev += argv[i];
    }
    ev += ")";
    rc = gmk_expand(ev.c_str());
  }
  return rc;
}

