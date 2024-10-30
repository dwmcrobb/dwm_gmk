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
//!  \file dwm_gmk_pushpop.cc
//!  \author Daniel W. McRobb
//!  \brief push and pop GNU make extension functions
//---------------------------------------------------------------------------

#include <cstring>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_push(const char *name, unsigned int argc, char *argv[])
{
  if (argc == 2 && strlen(argv[0]) && strlen(argv[1])) {
    std::string  expr(std::string(argv[0]) + " += " + argv[1]);
    gmk_floc  floc;
    gmk_eval(expr.c_str(), &floc);
  }
  return nullptr;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_popf(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if (argc == 1 && strlen(argv[0])) {
    std::deque<std::string>  d;
    Dwm::Gmk::ToDeque(argv[0], d);
    d.pop_front();
    std::string  s;
    Dwm::Gmk::ToString(d, s);
    rc = Dwm::Gmk::GmkCopy(s);
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_popb(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  if (argc == 1 && strlen(argv[0])) {
    std::deque<std::string>  d;
    Dwm::Gmk::ToDeque(argv[0], d);
    d.pop_back();
    std::string  s;
    Dwm::Gmk::ToString(d, s);
    rc = Dwm::Gmk::GmkCopy(s);
  }
  return rc;
}
