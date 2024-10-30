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
//!  \file DwmGmkMkfileStack.cc
//!  \author Daniel W. McRobb
//!  \brief Dwm::Gmk::MkfileStack class implementation
//---------------------------------------------------------------------------
extern "C" {
  #include <gnumake.h>
}

#include <filesystem>
#include <iostream>

#include "DwmGmkMkfileStack.hh"
#include "DwmGmkUtils.hh"

namespace Dwm {

  namespace Gmk {

    using namespace std;
    namespace fs = std::filesystem;

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MkfileStack::Push(const std::string & mkfile)
    {
      string  canon = fs::weakly_canonical(mkfile);
      {
        unique_lock  lck(_mtx);
        _stack.push_front(canon);
      }
      SetIncStackString();
      return;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MkfileStack::PushCurrent()
    {
      vector<string>  makefiles;
      Dwm::Gmk::GetMakefilesList(makefiles);
      string  mkfile = fs::weakly_canonical(makefiles.back());
      Push(mkfile);
      return;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MkfileStack::Pop()
    {
      {
        unique_lock  lck(_mtx);
        string  top = _stack.front();
        _stack.pop_front();
      }
      SetIncStackString();
      return;
    }
      
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MkfileStack::TopFile() const
    {
      shared_lock  lck(_mtx);
      return _stack.front();
    }
      
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MkfileStack::TopDir() const
    {
      shared_lock  lck(_mtx);
      return fs::path(_stack.front()).parent_path();
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MkfileStack::AsString() const
    {
      std::string  s;
      shared_lock  lck(_mtx);
      if (! _stack.empty()) {
        auto it = _stack.begin();
        s += *it;
        ++it;
        for (; it != _stack.end(); ++it) {
          s += ' ';
          s += *it;
        }
      }
      return s;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MkfileStack::SetIncStackString()
    {
      gmk_floc  floc = { __FILE__, __LINE__ };
      gmk_eval(string("dwm_incstack := " + AsString()).c_str(), &floc);
      return;
    }
      
  }  // namespace Gmk

}  // namespace Dwm
