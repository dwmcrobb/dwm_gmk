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
//!  \file DwmGmkMkfileStack.hh
//!  \author Daniel W. McRobb
//!  \brief Dwm::Gmk::MkfileStack class declaration
//---------------------------------------------------------------------------

#include <shared_mutex>
#include <deque>
#include <string>

namespace Dwm {

  namespace Gmk {

    //------------------------------------------------------------------------
    //!  Encapsulates a stack of Makefiles that we can use in 'dwm_include'
    //!  to keep track of the current Makefile.
    //------------------------------------------------------------------------
    class MkfileStack
    {
    public:
      void Push(const std::string & mkfile);
      void PushCurrent();
      void Pop();
      std::string TopFile() const;
      std::string TopDir() const;
      
    private:
      mutable std::shared_mutex  _mtx;
      std::deque<std::string>    _stack;

      std::string AsString() const;
      void SetIncStackString() const;
    };
    
  }  // namespace Gmk

}  // namespace Dwm
