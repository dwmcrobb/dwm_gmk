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
//!  \file DwmGmkUtils.cc
//!  \author Daniel W. McRobb
//!  \brief utility functions for dwmgmk GNU make extensions
//---------------------------------------------------------------------------

extern "C" {
  #include <gnumake.h>
}

#include <cstdlib>
#include <cstring>
#include <regex>

#include "DwmGmkUtils.hh"

namespace Dwm {

  namespace Gmk {

    using namespace std;
    namespace  fs = std::filesystem;

    static std::string  g_dwm_gmk_topdir_abs;
    
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
    bool ToVector(const std::string_view & s, vector<string> & v,
                  const string & rgxstr)
    {
      v.clear();
      regex  rgx(rgxstr, regex::ECMAScript|regex::optimize);
      regex_token_iterator it(s.begin(), s.end(), rgx, -1);
      std::cregex_token_iterator end;
      while (it != end) {
        v.push_back(*it++);
      }
      return (! v.empty());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToDeque(const std::string_view & s, std::deque<string> & d,
                 char sep)
    {
      d.clear();
      string::size_type  idx = 0;
      string::size_type  nextIdx;
      do {
        nextIdx = s.find_first_of(sep, idx);
        if (nextIdx != s.npos) {
          if (nextIdx > idx) {
            d.push_back(string(s.substr(idx, nextIdx - idx)));
          }
          idx = nextIdx + 1;
        }
      } while (nextIdx != s.npos);
      if (s.length() > idx) {
        d.push_back(string(s.substr(idx, s.length() - idx)));
      }
      return (! d.empty());
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
    bool ToString(const std::deque<string> & d, std::string & s, char sep)
    {
      s.clear();
      if (! d.empty()) {
        auto  it = d.cbegin();
        s += *it++;
        for ( ; it != d.cend(); ++it) {
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

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool GetMakefilesList(std::vector<std::string> & makefiles)
    {
      bool  rc = false;
      makefiles.clear();
      char  *mkfileList = gmk_expand("$(MAKEFILE_LIST)");
      if (mkfileList) {
        rc = ToVector(string_view(mkfileList), makefiles);
        gmk_free(mkfileList);
      }
      return rc;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string Pwd()
    {
      std::string  pwdstr;
      char  *pwd = getenv("PWD");
      if (pwd) {
        pwdstr = pwd;
      }
      return pwdstr;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string RelPwd(const std::string & p)
    {
      return fs::relative(p, Pwd());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string Top()
    {
      return g_dwm_gmk_topdir_abs;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void SetTop(const std::string & top)
    {
      g_dwm_gmk_topdir_abs = top;
      return;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string RelTop(const std::string & p)
    {
      return fs::relative(p, Top());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string Expand(const std::string & expr)
    {
      std::string  rc;
      char   *expanded = gmk_expand(expr.c_str());
      if (expanded) {
        rc = expanded;
        gmk_free(expanded);
      }
      return rc;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *GmkCopy(const std::string & s)
    {
      char  *cp = nullptr;
      if (! s.empty()) {
        cp = gmk_alloc(s.size() + 1);
        if (cp) {
          cp[s.size()] = 0;
          strncpy(cp, s.c_str(), s.size());
        }
      }
      return cp;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool GmkFiles(const std::string & p, const std::string & expr,
                  std::vector<std::string> & files)
    {
      files.clear();
      
      std::regex   rgx(expr, regex::ECMAScript | regex::optimize);
      std::smatch  sm;
      try {
        for (auto const & dirEntry : fs::directory_iterator{p}) {
          if (IsFile(dirEntry.path())) {
            std::string  fileName = dirEntry.path().filename().string();
            if (regex_match(fileName, sm, rgx)) {
              files.push_back(fileName);
            }
          }
        }
      }
      catch (...) {
      }
      return (! files.empty());
    }
    
  }  // namespace Gmk

}  // namespace Dwm

