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
#include <deque>
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
    //!  
    //------------------------------------------------------------------------
    bool ToVector(const std::string_view & s, std::vector<std::string> & v,
                  const std::string & rgxstr);

    //------------------------------------------------------------------------
    //!  Splits @c s on separator @c sep and puts each segment into @c d.
    //!  Returns true if the resulting @c d is non-empty.
    //------------------------------------------------------------------------
    bool ToDeque(const std::string_view & s, std::deque<std::string> & v,
                 char sep = ' ');
    
    //------------------------------------------------------------------------
    //!  Populates @c s by concatenating the elements of @c v with @c sep as
    //!  a separator.  Returns true if the resulting @c s is non-empty.
    //------------------------------------------------------------------------
    bool ToString(const std::vector<std::string> & v, std::string & s,
                  char sep = ' ');

    //------------------------------------------------------------------------
    //!  Populates @c s by concatenating the elements of @c d with @c sep as
    //!  a separator.  Returns true if the resulting @c s is non-empty.
    //------------------------------------------------------------------------
    bool ToString(const std::deque<std::string> & d, std::string & s,
                  char sep = ' ');
    
    //------------------------------------------------------------------------
    //!  Returns true if @c p appears to be a file (regular, block special,
    //!  character special, FIFO or socket.
    //------------------------------------------------------------------------
    bool IsFile(const std::filesystem::path & p);

    //------------------------------------------------------------------------
    //!  Puts the contents of MAKEFILE_LIST into @c makefiles.
    //------------------------------------------------------------------------
    bool GetMakefilesList(std::vector<std::string> & makefiles);

    //------------------------------------------------------------------------
    //!  Returns the value of the PWD environment variable.
    //------------------------------------------------------------------------
    std::string Pwd();

    //------------------------------------------------------------------------
    //!  Returns the relative path from Pwd() to the given path @c p.
    //------------------------------------------------------------------------
    std::string RelPwd(const std::string & p);

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string Top();

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void SetTop(const std::string & top);

    //------------------------------------------------------------------------
    //!  Returns the relative path from Top() to the given path @c p.
    //------------------------------------------------------------------------
    std::string RelTop(const std::string & p);

    //------------------------------------------------------------------------
    //!  Returns the GNU make expansion of @c expr.
    //------------------------------------------------------------------------
    std::string Expand(const std::string & expr);

    //------------------------------------------------------------------------
    //!  Returns a pointer to a C-style string copy of @c s that was allocated
    //!  with gmk_alloc().
    //------------------------------------------------------------------------
    char *GmkCopy(const std::string & s);

    //------------------------------------------------------------------------
    //!  Populate @c files with all files in directory at path @c p whose
    //!  filename matches the ECMAScript regular expression @c expr.  Returns
    //!  true if any filenames matched (same as (! files.empty())).
    //------------------------------------------------------------------------
    bool GmkFiles(const std::string & p, const std::string & expr,
                  std::vector<std::string> & files);

    //------------------------------------------------------------------------
    //!  Returns the unique entries of @c v as a concantenated string,
    //!  retaining the leftmost duplicates (removing the rightmost).
    //------------------------------------------------------------------------
    std::string UniqLeft(const std::vector<std::string> & v);
    
    //------------------------------------------------------------------------
    //!  Returns the unique substrings of @c s as a concantenated string,
    //!  retaining the lefttmost duplicates (removing the rightmost).
    //!  Substrings are strings with no spaces (space is the separator).
    //------------------------------------------------------------------------
    std::string UniqLeft(const std::string & s);

    //------------------------------------------------------------------------
    //!  Returns the unique entries of @c v as a concantenated string,
    //!  retaining the rightmost duplicates (removing the lefttmost).
    //------------------------------------------------------------------------
    std::string UniqRight(const std::vector<std::string> & v);

    //------------------------------------------------------------------------
    //!  Returns the unique substrings of @c s as a concantenated string,
    //!  retaining the rightmost duplicates (removing the lefttmost).
    //!  Substrings are strings with no spaces (space is the separator).
    //------------------------------------------------------------------------
    std::string UniqRight(const std::string & s);
    
  }  // namespace Gmk
  
}  // namespace Dwm

