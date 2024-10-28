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

#include <filesystem>
#include <iostream>
#include <stack>
#include <string>

#include "dwm_gmk.h"
#include "DwmGmkMkfileStack.hh"
#include "DwmGmkUtils.hh"

extern "C" {
    int plugin_is_GPL_compatible = 1;
}

Dwm::Gmk::MkfileStack    g_mkfileStack;

//---------------------------------------------------------------------------
//!  
//---------------------------------------------------------------------------
int dwm_gmk_setup(const gmk_floc *floc)
{
  std::string  dwm_funcs("dwm_funcs :=");
  for (auto & fn : dwm_gmk_function_entries) {
    gmk_add_function(fn.name, fn.fn, fn.min_args, fn.max_args, fn.flags);
    dwm_funcs += ' ';
    dwm_funcs += fn.name;
  }
  gmk_eval(dwm_funcs.c_str(), floc);
  g_mkfileStack.PushCurrent();
  return 1;
}

