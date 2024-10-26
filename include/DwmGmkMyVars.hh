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

      using  PerNamespaceMap = std::unordered_map<std::string,VarData>;
      using  Namespace = std::string;

      mutable std::shared_mutex                      _mtx;
      std::unordered_map<std::string,std::string>    _namespaces;
      std::unordered_map<Namespace,PerNamespaceMap>  _vars;

      static std::string GetExprRHS(const std::vector<std::string> & args);
    };
    
  }  // namespace Gmk

}  // namespace Dwm
