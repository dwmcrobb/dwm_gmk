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
#include <regex>

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
        string  exprExpanded = Expand(exprStr);
        if (exprVec[1] == ":=") {
          unique_lock  lck(_mtx);
          _vars[ns][varName].value = exprExpanded;
          _vars[ns][varName].expand = false;
        }
        else if (exprVec[1] == "=") {
          unique_lock  lck(_mtx);
          _vars[ns][varName].value = exprStr;
          _vars[ns][varName].expand = true;
        }
        else if (exprVec[1] == "+=") {
          unique_lock  lck(_mtx);
          auto  it = _vars[ns].find(varName);
          if (it == _vars[ns].end()) {
            _vars[ns][varName].value = exprStr;
            _vars[ns][varName].expand = true;
          }
          else {
            if (it->second.expand) {
              it->second.value += ' ';
              it->second.value += exprStr;
            }
            else {
              it->second.value += ' ';
              it->second.value += exprExpanded;
            }
          }
        }
      }
      return;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MyVars::SetVarValueImmediate(const std::string & varName,
                                      const std::string & varValue)
    {
      vector<string>  varNameElements;
      string          myVarName(varName);
      string          ns;
      if (ToVector(varName, varNameElements, '.')
          && (varNameElements.size() == 2)) {
        ns = varNameElements[0];
        myVarName = varNameElements[1];
      }
      else {
        ns = GetNamespaceString();
      }
      unique_lock  lck(_mtx);
      _vars[ns][myVarName].value = varValue;
      _vars[ns][myVarName].expand = false;
      return;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetVarValue(const std::string & varName)
    {
      char  *value = nullptr;
      string  valuestr = GetVarValueString(varName);
      if (! valuestr.empty()) {
        value = GmkCopy(valuestr);
      }
      return value;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MyVars::GetVarValueString(const std::string & varName)
    {
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
      return GetVarValueString(ns, realVarName);
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MyVars::GetVarValuesString(unsigned int argc, char *argv[])
    {
      string  varValues;
      string  spc;
      for (unsigned int i = 0; i < argc; ++i) {
        string  varValue = GetVarValueString(argv[i]);
        if (! varValue.empty()) {
          varValues += spc;
          varValues += varValue;
          spc = " ";
        }
      }
      return varValues;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetVarValues(unsigned int argc, char *argv[])
    {
      char    *varValues = nullptr;
      string   varValuesStr = GetVarValuesString(argc, argv);
      if (! varValuesStr.empty()) {
        varValues = GmkCopy(varValuesStr);
      }
      return varValues;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetVarValue(const std::string & ns,
                              const std::string & varName)
    {
      char  *value = nullptr;
      string  valuestr = GetVarValueString(ns, varName);
      if (! valuestr.empty()) {
        value = GmkCopy(valuestr);
      }
      return value;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MyVars::GetVarValueString(const std::string & ns,
                                          const std::string & varName)
    {
      string       value;
      shared_lock  lck(_mtx);
      auto         nsiter = _vars.find(ns);
      if (nsiter != _vars.end()) {
        auto  viter = nsiter->second.find(varName);
        if (viter != nsiter->second.end()) {
          if (viter->second.expand) {
            char  *valuep = gmk_expand(viter->second.value.c_str());
            if (valuep) {
              value = valuep;
              gmk_free(valuep);
            }
          }
          else {
            value = viter->second.value;
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
    std::string MyVars::GetVarValuesString(const std::string & rgxstr)
    {
      string  valuesStr;
      regex   rgx(rgxstr,std::regex::ECMAScript|std::regex::optimize);
      smatch  sm;
      string  spc;
      
      for (const auto & ns : _vars) {
        for (const auto & var : ns.second) {
          string  fqvarname(ns.first + "." + var.first);
          if (regex_match(fqvarname, sm, rgx)) {
            char  *value = nullptr;
            if (var.second.expand) {
              value = gmk_expand(var.second.value.c_str());
            }
            else {
              value = GmkCopy(var.second.value);
            }
            if (value) {
              valuesStr += spc;
              valuesStr += value;
              spc = " ";
              gmk_free(value);
            }
          }
        }
      }
      return valuesStr;
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
