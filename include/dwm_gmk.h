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
//!  \file dwm_gmk.h
//!  \author Daniel W. McRobb
//!  \brief dwmgmk GNU make extension function declarations
//---------------------------------------------------------------------------

extern "C" {
    #include <gnumake.h>
    
    extern int plugin_is_GPL_compatible;

    int dwm_gmk_setup(const gmk_floc *floc);
    char *dwm_gmk_init(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_bison(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_curpath(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_dirfiles(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_flex(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_fromtop(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_pwd(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_relpath(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_relpwd(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_settop(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_subdirs(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_thisdir(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_top(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_totop(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_uniqsort(const char *name, unsigned int argc, char *argv[]);
}
