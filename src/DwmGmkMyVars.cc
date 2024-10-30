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
//!  \file DwmGmkMyVars.cc
//!  \author Daniel W. McRobb
//!  \brief Dwm::Gmk::MyVars class implementation
//---------------------------------------------------------------------------

extern "C" {
  #include <gnumake.h>
}

#include <algorithm>
#include <iostream>
#include <mutex>

#include "DwmGmkMyVars.hh"
#include "DwmGmkMkfileStack.hh"
#include "DwmGmkUtils.hh"

extern Dwm::Gmk::MkfileStack  g_mkfileStack;

namespace Dwm {

  namespace Gmk {

    using namespace std;

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    static string NamespaceKeyFromMkFile()
    {
      string  nskey = g_mkfileStack.TopFile();
      std::replace(nskey.begin(), nskey.end(), '/', '_');
      std::replace(nskey.begin(), nskey.end(), '.', '_');
      return nskey;
    }
      
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MyVars::SetNamespace(const std::string & ns)
    {
      string  nskey = NamespaceKeyFromMkFile();
      unique_lock lck(_mtx);
      _namespaces[nskey] = ns;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetNamespace() const
    {
      return GmkCopy(GetNamespaceString());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    string MyVars::GetNamespaceString() const
    {
      string  ns;
      string  nskey = NamespaceKeyFromMkFile();
      shared_lock  lck(_mtx);
      auto  it = _namespaces.find(nskey);
      if (it != _namespaces.end()) {
        ns = it->second;
      }
      return ns;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MyVars::SetVarValue(const std::vector<std::string> & exprVec)
    {
      string  varValue;
      if (exprVec.size() >= 3) {
        string  varName(exprVec[0]);
        string  exprStr = GetExprRHS(exprVec);
        vector<string>  varNameElements;
        string  ns;
        if (ToVector(varName, varNameElements, '.')
            && (varNameElements.size() == 2)) {
          ns = varNameElements[0];
          varName = varNameElements[1];
        }
        else {
          ns = GetNamespaceString();
        }
        if (exprVec[1] == ":=") {
          string  exprExpanded = Expand(exprStr);
          unique_lock  lck(_mtx);
          _vars[ns][varName].value = exprExpanded;
          _vars[ns][varName].expand = false;
        }
        else if (exprVec[1] == "=") {
          unique_lock  lck(_mtx);
          _vars[ns][varName].value = exprStr;
          _vars[ns][varName].expand = true;
        }
      }
      return;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetVarValue(const std::string & varName)
    {
      char  *value = nullptr;
      vector<string>  varNameElements;
      string    ns;
      string    realVarName(varName);
      if (ToVector(varName, varNameElements, '.')
          && (varNameElements.size() == 2)) {
        ns = varNameElements[0];
        realVarName = varNameElements[1];
      }
      else {
        ns = GetNamespaceString();
      }
      value = GetVarValue(ns, realVarName);
      return value;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetVarValue(const std::string & ns,
                              const std::string & varName)
    {
      char  *value = nullptr;
      shared_lock  lck(_mtx);
      auto   nsiter = _vars.find(ns);
      if (nsiter != _vars.end()) {
        auto  viter = nsiter->second.find(varName);
        if (viter != nsiter->second.end()) {
          if (viter->second.expand) {
            value = gmk_expand(viter->second.value.c_str());
          }
          else {
            value = GmkCopy(viter->second.value);
          }
        }
      }
      return value;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetVarNames(const std::string & ns)
    {
      char    *names = nullptr;
      string   namesStr = GetVarNamesString(ns);
      if (! namesStr.empty()) {
        names = GmkCopy(namesStr);
      }
      return names;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MyVars::GetVarNamesString(const std::string & ns)
    {
      string   names;
      shared_lock  lck(_mtx);
      auto   nsiter = _vars.find(ns);
      if (nsiter != _vars.end()) {
        string  spc;
        for (const auto & var : nsiter->second) {
          names += spc;
          names += var.first;
          spc = " ";
        }
      }
      return names;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetVarNames()
    {
      char         *names = nullptr;
      string        namesStr;
      shared_lock   lck(_mtx);
      string        spc;
      for (const auto & ns : _vars) {
        for (const auto & var : ns.second) {
          namesStr += spc;
          namesStr += ns.first + '.' + var.first;
          spc = " ";
        }
      }
      if (! namesStr.empty()) {
        names = GmkCopy(namesStr);
      }
      return names;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    string MyVars::GetExprRHS(const vector<string> & args)
    {
      string  rhs;
      if (args.size() >= 3) {
        rhs = args[2];
        for (size_t i = 3; i < args.size(); ++i) {
          rhs += ' ';
          rhs += args[i];
        }
      }
      return rhs;
    }

    
  }  // namespace Gmk

}  // namespace Dwm
