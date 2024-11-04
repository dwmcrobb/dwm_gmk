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

#include <vector>

extern "C" {
    #include <gnumake.h>
    
    extern int plugin_is_GPL_compatible;

    int dwm_gmk_setup(const gmk_floc *floc);
    char *dwm_gmk_aliasfn(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_bison(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_cppdeps(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_curpath(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_files(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_flex(const char *name, unsigned int argc, char *argv[]);
  
    //-----------------------------------------------------------------------
    //!  If called from a makefile in the current directory (CURDIR), returns
    //!  argv[0].  Else returns argv[1].  Note this requires 'dwm_include' to
    //!  always be used instead of 'include' in order for the directory of
    //!  the makefile to be correctly tracked.
    //-----------------------------------------------------------------------
    char *dwm_gmk_ifcwd(const char *name, unsigned int argc, char *argv[]);
    
    char *dwm_gmk_include(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_include_once(const char *name, unsigned int argc, char *argv[]);

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
    //!  returns all variables that were set via 'my ...' in the namespace
    //!  argv[0].
    //-----------------------------------------------------------------------
    char *dwm_gmk_myvn(const char *name, unsigned int argc, char *argv[]);

    //-----------------------------------------------------------------------
    //!  Returns the values of all private variables whose name matches the
    //!  regular expression in @c argv[0], as a concatenated string.  I use
    //!  this to get similarly named variables of subdirectory makefiles
    //!  that I've included from a parent directory makefile.
    //-----------------------------------------------------------------------
    char *dwm_gmk_myvrgx(const char *name, unsigned int argc, char *argv[]);
  
    char *dwm_gmk_popb(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_popf(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_push(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_pwd(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_relpath(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_relpwd(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_reverse(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_rgxmatch(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_rgxreplace(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_rgxsearch(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_rgxsubst(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_rotl(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_rotr(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_setltlibvars(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_sort(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_subdirs(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_thisdir(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_uniqleft(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_uniqright(const char *name, unsigned int argc, char *argv[]);
    char *dwm_gmk_vrgx(const char *name, unsigned int argc, char *argv[]);

  typedef struct {
    const char    *name;
    gmk_func_ptr   fn;
    unsigned int   min_args;
    unsigned int   max_args;
    unsigned int   flags;
  } dwm_gmk_fn_entry;

  //  Would be nice if GNU make built-in functions were accessible
  //  (not static)...

  typedef char *(*builtin_fn_ptr)(char *o, char **argv, const char *funcname);

  typedef struct {
    const char      *name;
    unsigned int     min_args;
    unsigned int     max_args;
    unsigned int     flags;
  } dwm_gmk_bi_fn_entry;
    
  char *dwm_gmk_call_builtin(const char *name, unsigned int argc,
                             char *argv[]);
}

extern std::vector<dwm_gmk_fn_entry>     dwm_gmk_function_entries;

