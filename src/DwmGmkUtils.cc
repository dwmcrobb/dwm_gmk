#include "DwmGmkUtils.hh"

namespace Dwm {

  namespace Gmk {

    using namespace std;
      
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToVector(const std::string & s, std::vector<string> & v, char sep)
    {
      v.clear();
      string::size_type  idx = 0;
      string::size_type  nextIdx;
      do {
        nextIdx = s.find_first_of(sep, idx);
        if (nextIdx != s.npos) {
          if (nextIdx > idx) {
            v.push_back(s.substr(idx, nextIdx - idx));
          }
          idx = nextIdx + 1;
        }
      } while (nextIdx != s.npos);
      if (s.length() > idx) {
        v.push_back(s.substr(idx, s.length() - idx));
      }
      return (! v.empty());
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToVector(const std::string_view & s, std::vector<string> & v,
                  char sep)
    {
      v.clear();
      string::size_type  idx = 0;
      string::size_type  nextIdx;
      do {
        nextIdx = s.find_first_of(sep, idx);
        if (nextIdx != s.npos) {
          if (nextIdx > idx) {
            v.push_back(string(s.substr(idx, nextIdx - idx)));
          }
          idx = nextIdx + 1;
        }
      } while (nextIdx != s.npos);
      if (s.length() > idx) {
        v.push_back(string(s.substr(idx, s.length() - idx)));
      }
      return (! v.empty());
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    bool ToString(const std::vector<string> & v, std::string & s)
    {
      s.clear();
      if (! v.empty()) {
        auto  it = v.cbegin();
        s += *it++;
        for ( ; it != v.cend(); ++it) {
          s += ' ';
          s += *it;
        }
      }
      return (! s.empty());
    }
    
  }  // namespace Gmk

}  // namespace Dwm

