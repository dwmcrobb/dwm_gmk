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
//!  \file dwm_gmk_bison.cc
//!  \author Daniel W. McRobb
//!  \brief utility functions for dwmgmk GNU make extensions
//---------------------------------------------------------------------------

#include "DwmGmkUtils.hh"

namespace Dwm {

  namespace Gmk {

    using namespace std;
    namespace  fs = std::filesystem;
      
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToVector(const std::string & s, std::vector<string> & v, char sep)
    {
      v.clear();
      string::size_type  idx = 0;
      string::size_type  nextIdx;
      do {
        nextIdx = s.find_first_of(sep, idx);
        if (nextIdx != s.npos) {
          if (nextIdx > idx) {
            v.push_back(s.substr(idx, nextIdx - idx));
          }
          idx = nextIdx + 1;
        }
      } while (nextIdx != s.npos);
      if (s.length() > idx) {
        v.push_back(s.substr(idx, s.length() - idx));
      }
      return (! v.empty());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToVector(const std::string_view & s, std::vector<string> & v,
                  char sep)
    {
      v.clear();
      string::size_type  idx = 0;
      string::size_type  nextIdx;
      do {
        nextIdx = s.find_first_of(sep, idx);
        if (nextIdx != s.npos) {
          if (nextIdx > idx) {
            v.push_back(string(s.substr(idx, nextIdx - idx)));
          }
          idx = nextIdx + 1;
        }
      } while (nextIdx != s.npos);
      if (s.length() > idx) {
        v.push_back(string(s.substr(idx, s.length() - idx)));
      }
      return (! v.empty());
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToString(const std::vector<string> & v, std::string & s, char sep)
    {
      s.clear();
      if (! v.empty()) {
        auto  it = v.cbegin();
        s += *it++;
        for ( ; it != v.cend(); ++it) {
          s += sep;
          s += *it;
        }
      }
      return (! s.empty());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool IsFile(const fs::path & p)
    {
      bool  rc = false;
      fs::file_status  s = fs::status(p);
      switch (s.type()) {
        case fs::file_type::regular:
        case fs::file_type::block:
        case fs::file_type::character:
        case fs::file_type::fifo:
        case fs::file_type::socket:
          rc = true;
          break;
        default:
          break;
      }
      return rc;
    }
    
  }  // namespace Gmk

}  // namespace Dwm

