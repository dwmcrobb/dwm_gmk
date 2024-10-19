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
//!  \file dwm_gmk_setup.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_setup GNU make extension function
//---------------------------------------------------------------------------

#include "dwm_gmk.h"

extern "C" {
    int plugin_is_GPL_compatible = 1;
}

//---------------------------------------------------------------------------
//!  
//---------------------------------------------------------------------------
int dwm_gmk_setup(const gmk_floc *floc)
{
    gmk_add_function("dwm_gmk_init", dwm_gmk_init, 0, 0, 0);

    gmk_add_function("dwm_bison",       dwm_gmk_bison, 1, 0, 0);
    gmk_add_function("dwm_curpath",     dwm_gmk_curpath, 0, 0, 0);
    gmk_add_function("dwm_cwd",         dwm_gmk_curpath, 0, 0, 0);
    gmk_add_function("dwm_dirfiles",    dwm_gmk_dirfiles, 0, 2, 0);
    gmk_add_function("dwm_flex",        dwm_gmk_flex, 1, 1, 0);
    gmk_add_function("dwm_fromtop",     dwm_gmk_fromtop, 0, 1, 0);
    gmk_add_function("dwm_pwd",         dwm_gmk_pwd, 0, 0, 0);
    gmk_add_function("dwm_relpath",     dwm_gmk_relpath, 2, 2, 0);
    gmk_add_function("dwm_relpwd",      dwm_gmk_relpwd, 1, 1, 0);
    gmk_add_function("dwm_rgxmatch",    dwm_gmk_rgxmatch, 2, 2, 0);
    gmk_add_function("dwm_rgxreplace",  dwm_gmk_rgxreplace, 3, 3, 0);
    gmk_add_function("dwm_rgxsearch",   dwm_gmk_rgxsearch, 2, 2, 0);
    gmk_add_function("dwm_rgxsubst",    dwm_gmk_rgxsubst, 3, 3, 0);
    gmk_add_function("dwm_settop",      dwm_gmk_settop, 0, 1, 0);
    gmk_add_function("dwm_subdirs",     dwm_gmk_subdirs, 0, 2, 0);
    gmk_add_function("dwm_thisdir",     dwm_gmk_thisdir, 0, 0, 0);
    gmk_add_function("dwm_top",         dwm_gmk_top, 0, 0, 0);
    gmk_add_function("dwm_totop",       dwm_gmk_totop, 0, 1, 0);
    gmk_add_function("dwm_uniqsort",    dwm_gmk_uniqsort, 1, 1, 0);
    
    return 1;
}

