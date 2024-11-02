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
//!  \file dwm_gmk_ifcwd.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_ifcwd GNU make extension function
//---------------------------------------------------------------------------

#include <cstring>
#include <iostream>

#include "dwm_gmk.h"
#include "DwmGmkMkfileStack.hh"
#include "DwmGmkUtils.hh"

using namespace std;

extern Dwm::Gmk::MkfileStack  g_mkfileStack;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_ifcwd(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if (argc == 2) {
    char  *CURDIR = gmk_expand("$(CURDIR)");
    if (CURDIR) {
      string  curdirstr = CURDIR;
      gmk_free(CURDIR);
      if (g_mkfileStack.TopDir() == curdirstr) {
        if (strlen(argv[0])) {
          string rcstr = argv[0];
          rc = Dwm::Gmk::GmkCopy(rcstr);
        }
      }
      else {
        if (strlen(argv[1])) {
          string rcstr = argv[1];
          rc = Dwm::Gmk::GmkCopy(rcstr);
        }
      }
    }
  }
  return rc;
}
