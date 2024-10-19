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
//!  \file dwm_gmk_relpwd.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_relpwd GNU make extension function
//---------------------------------------------------------------------------

#include <cstdlib>

#include "dwm_gmk.h"

//----------------------------------------------------------------------------
//!  Note that we're counting on the shell to set the PWD environment
//!  variable, and for it not to be changed by GNU make.
//----------------------------------------------------------------------------
char *dwm_gmk_relpwd(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  if (argc == 1) {
    char  *paths[2] = { getenv("PWD"), argv[0] };
    rc = dwm_gmk_relpath("dwm_relpath", 2, paths);
  }
  return rc;
}

