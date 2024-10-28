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
//!  \file dwm_gmk_pwd.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_pwd GNU make extension function
//---------------------------------------------------------------------------

#include "dwm_gmk.h"

#include <cstdlib>
#include <cstring>

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_pwd(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = 0;
  char  *PWD = getenv("PWD");
  if (PWD) {
    rc = gmk_alloc(strlen(PWD) + 1);
    if (rc) {
      rc[strlen(PWD)] = 0;
      strncpy(rc, PWD, strlen(PWD));
    }
  }
  return rc;
}
