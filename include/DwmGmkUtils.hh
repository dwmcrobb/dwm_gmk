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
//!  \file dwm_gmk.h
//!  \author Daniel W. McRobb
//!  \brief dwmgmk utility function declarations
//---------------------------------------------------------------------------

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace Dwm {

  namespace Gmk {

    //------------------------------------------------------------------------
    //!  Splits @c s on separator @c sep and puts each segment into @c v.
    //!  Returns true if the resulting @c v is non-empty.
    //------------------------------------------------------------------------
    bool ToVector(const std::string & s, std::vector<std::string> & v,
                  char sep = ' ');

    //------------------------------------------------------------------------
    //!  Splits @c s on separator @c sep and puts each segment into @c v.
    //!  Returns true if the resulting @c v is non-empty.
    //------------------------------------------------------------------------
    bool ToVector(const std::string_view & s, std::vector<std::string> & v,
                  char sep = ' ');

    //------------------------------------------------------------------------
    //!  Populates @c s by concatenating the elements of @c with @c sep as
    //!  a separator.  Returns true if the resulting @c s is non-empty.
    //------------------------------------------------------------------------
    bool ToString(const std::vector<std::string> & v, std::string & s,
                  char sep = ' ');

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool IsFile(const std::filesystem::path & p);
      

  }  // namespace Gmk

}  // namespace Dwm

