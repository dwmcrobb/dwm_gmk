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
//!  \file dwm_gmk_rotate.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk rotate GNU make extension functions
//---------------------------------------------------------------------------

#include <algorithm>
#include <cstring>
#include <iostream>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_rotl(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  size_t  pos = 1;
  if (argc > 0) {
    std::string_view  sv(argv[0]);
    std::vector<std::string>  v;
    if (Dwm::Gmk::ToVector(sv, v)) {
      if (argc > 1) {
        try {
          pos = std::stoul(argv[1]);
        }
        catch (...) {
          std::cerr << "dwm_rotl: second argument " << argv[1]
                    << " is not integer\n";
          return nullptr;
        }
      }
      if (pos && (pos > v.size())) {
        pos %= v.size();
      }
      if (pos) {
        std::rotate(v.begin(), v.begin() + pos, v.end());
      }
      std::string  s;
      Dwm::Gmk::ToString(v, s);
      rc = Dwm::Gmk::GmkCopy(s.c_str());
    }
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_rotr(const char *name, unsigned int argc, char *argv[])
{
  char  *rc = nullptr;
  size_t  pos = 1;
  if (argc > 0) {
    std::string_view  sv(argv[0]);
    std::vector<std::string>  v;
    if (Dwm::Gmk::ToVector(sv, v)) {
      if (argc > 1) {
        try {
          pos = std::stoul(argv[1]);
        }
        catch (...) {
          std::cerr << "dwm_rotl: second argument " << argv[1]
                    << " is not integer\n";
          return nullptr;
        }
      }
      if (pos && (pos > v.size())) {
        pos %= v.size();
      }
      if (pos) {
        std::rotate(v.rbegin(), v.rbegin() + pos, v.rend());
      }
      std::string  s;
      Dwm::Gmk::ToString(v, s);
      rc = Dwm::Gmk::GmkCopy(s.c_str());
    }
  }
  return rc;
}
