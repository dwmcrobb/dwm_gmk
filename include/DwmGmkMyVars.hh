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
//!  \file DwmGmkMyVars.hh
//!  \author Daniel W. McRobb
//!  \brief Dwm::Gmk::MyVars class declaration
//---------------------------------------------------------------------------
#include <shared_mutex>
#include <string>
#include <map>

namespace Dwm {

  namespace Gmk {

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    class MyVars
    {
    public:
      void SetNamespace(const std::string & ns);
      char *GetNamespace() const;
      std::string GetNamespaceString() const;
      void SetVarValue(const std::vector<std::string> & exprVec);
      char *GetVarValue(const std::string & varName);
      char *GetVarValue(const std::string & ns,
                        const std::string & varName);
      char *GetVarNames(const std::string & ns);
      char *GetVarNames();
      std::string GetVarNamesString(const std::string & ns);
      
    private:
      typedef struct {
        std::string  value;
        bool         expand;
      } VarData;

      using  PerNamespaceMap = std::map<std::string,VarData>;
      using  Namespace = std::string;

      mutable std::shared_mutex            _mtx;
      std::map<std::string,std::string>    _namespaces;
      std::map<Namespace,PerNamespaceMap>  _vars;

      static std::string GetExprRHS(const std::vector<std::string> & args);
    };
    
  }  // namespace Gmk

}  // namespace Dwm
