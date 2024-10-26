#include <shared_mutex>
#include <deque>
#include <string>

namespace Dwm {

  namespace Gmk {

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    class MkfileStack
    {
    public:
      void Push(const std::string & mkfile);
      void PushCurrent();
      void Pop();
      std::string TopFile() const;
      std::string TopDir() const;
      std::string AsString() const;
      
    private:
      mutable std::shared_mutex  _mtx;
      std::deque<std::string>    _stack;
    };
    
  }  // namespace Gmk

}  // namespace Dwm
