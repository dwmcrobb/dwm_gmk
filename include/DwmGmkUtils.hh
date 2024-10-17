#include <string>
#include <string_view>
#include <vector>

namespace Dwm {

  namespace Gmk {

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToVector(const std::string & s, std::vector<std::string> & v,
                  char sep = ' ');

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToVector(const std::string_view & s, std::vector<std::string> & v,
                  char sep = ' ');

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToString(const std::vector<std::string> & v, std::string & s);

  }  // namespace Gmk

}  // namespace Dwm

