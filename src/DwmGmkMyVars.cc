extern "C" {
  #include <gnumake.h>
}

#include "DwmGmkMyVars.hh"
#include "DwmGmkUtils.hh"

namespace Dwm {

  namespace Gmk {

    using namespace std;
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MyVars::SetNamespace(const std::string & ns)
    {
      unique_lock lck(_mtx);
      _ns = ns;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    char *MyVars::GetNamespace()
    {
      return GmkCopy(GetNamespaceString());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    string MyVars::GetNamespaceString()
    {
      shared_lock  lck(_mtx);
      return _ns;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MyVars::SetVarValue(const std::vector<std::string> & exprVec)
    {
      string  varValue;
      if (exprVec.size() >= 3) {
        string  varName(exprVec[0]);
        if (exprVec[1] == ":=") {
          string  exprStr = GetExprRHS(exprVec);
          string  exprExpanded = Expand(exprStr);
          unique_lock  lck(_mtx);
          _vars[_ns][varName].value = exprExpanded;
          _vars[_ns][varName].expand = false;
        }
        else if (exprVec[1] == "=") {
          string  exprStr = GetExprRHS(exprVec);
          unique_lock  lck(_mtx);
          _vars[_ns][varName].value = exprStr;
          _vars[_ns][varName].expand = true;
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
      shared_lock  lck(_mtx);
      auto   nsiter = _vars.find(_ns);
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
