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
    
    char *dwm_gmk_bison(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_cppdeps(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_curpath(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_files(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_flex(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_fromtop(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_include(const char *name, unsigned int argc, char *argv[]);

    //-----------------------------------------------------------------------
    //!  Assigns a value to a variable in a non-global namespace or returns
    //!  a variable's value from a non-global namespace.  If argv[0] is of
    //!  the form 'foo := ...' or 'foo = ...', assigns the variable's value
    //!  (immediate or deferred, respectively).  If argv[0] is of the form
    //!  'foo', returns the variable's value (nil if the variable does not
    //!  exit).  The namespace can be specified if the variable name is of
    //!  the form 'bar.foo', where 'bar' is the namespace.  Else the
    //!  namespace is assumed to be the last namespace assigned with
    //!  'myns'.
    //-----------------------------------------------------------------------
    char *dwm_gmk_my(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_myns(const char *name, unsigned int argc, char *argv[]);
    
    //-----------------------------------------------------------------------
    //!  With an empty argv[0], returns a space-separated list of all
    //!  all variables that were set via 'my ...', with each variable name
    //!  fully qualified ('namespace.varname').  With a non-empty argv[0],
    //!  returns all variables that were set via 'my ...' from the namespace
    //!  argv[0].
    //-----------------------------------------------------------------------
    char *dwm_gmk_myvn(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_pwd(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_relpath(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_relpwd(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_rgxmatch(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_rgxreplace(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_rgxsearch(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_rgxsubst(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_settop(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_sort(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_subdirs(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_thisdir(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_top(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_totop(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_uniqleft(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_uniqright(const char *name, unsigned int argc, char *argv[]);
}
