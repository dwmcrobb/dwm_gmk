#include <filesystem>
#include <iostream>

#include "DwmGmkMkfileStack.hh"
#include "DwmGmkUtils.hh"

namespace Dwm {

  namespace Gmk {

    using namespace std;
    namespace fs = std::filesystem;

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MkfileStack::Push(const std::string & mkfile)
    {
      string  canon = fs::weakly_canonical(mkfile);
      // cerr << "MkfileStack::Push(" << canon << ")\n";
      unique_lock  lck(_mtx);
      _stack.push_front(canon);
      return;
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MkfileStack::PushCurrent()
    {
      vector<string>  makefiles;
      Dwm::Gmk::GetMakefilesList(makefiles);
      string  mkfile = fs::weakly_canonical(makefiles.back());
      Push(mkfile);
      return;
    }
    
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    void MkfileStack::Pop()
    {
      unique_lock  lck(_mtx);
      string  top = _stack.front();
      _stack.pop_front();
#if 0
      cerr << "MkfileStack popped " << top << ", new top "
           << _stack.front() << '\n';
#endif
      return;
    }
      
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MkfileStack::TopFile() const
    {
      shared_lock  lck(_mtx);
      return _stack.front();
    }
      
    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MkfileStack::TopDir() const
    {
      shared_lock  lck(_mtx);
      return fs::path(_stack.front()).parent_path();
    }

    //------------------------------------------------------------------------
    //!  
    //------------------------------------------------------------------------
    std::string MkfileStack::AsString() const
    {
      std::string  s;
      if (! _stack.empty()) {
        auto it = _stack.begin();
        s += *it;
        ++it;
        for (; it != _stack.end(); ++it) {
          s += ' ';
          s += *it;
        }
      }
      return s;
    }
    
  }  // namespace Gmk

}  // namespace Dwm
