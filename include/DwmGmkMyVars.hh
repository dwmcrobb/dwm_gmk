#include <shared_mutex>
#include <string>
#include <unordered_map>

namespace Dwm {

  namespace Gmk {

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    class MyVars
    {
    public:
      void SetNamespace(const std::string & ns);
      char *GetNamespace();
      std::string GetNamespaceString();
      void SetVarValue(const std::vector<std::string> & exprVec);
      char *GetVarValue(const std::string & varName);
      
    private:
      typedef struct {
        std::string  value;
        bool         expand;
      } VarData;

      using  PerNamespaceMap = std::unordered_map<std::string,VarData>;
      using  Namespace = std::string;

      mutable std::shared_mutex                      _mtx;
      std::string                                    _ns;
      std::unordered_map<Namespace,PerNamespaceMap>  _vars;

      static std::string GetExprRHS(const std::vector<std::string> & args);
    };
    
  }  // namespace Gmk

}  // namespace Dwm
