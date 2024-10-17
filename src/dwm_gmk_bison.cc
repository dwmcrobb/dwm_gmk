#include <iostream>
#include <string>

#include "dwm_gmk.h"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_bison(const char *name, unsigned int argc, char *argv[])
{
  using namespace std;
  
  if ((argc == 1) && argv[0]) {
    std::string  rule;
    std::string  _bison_targets = "$(patsubst %.y,%.cc," + string(argv[0])
      + ") $(patsubst %.y,%.hh," + string(argv[0]) + ')';
    char  *tmp = gmk_expand(_bison_targets.c_str());
    if (! tmp) {
      cerr << "Failed to expand " << _bison_targets << '\n';
      return 0;
    }
    _bison_targets = tmp;
    gmk_free(tmp);
    rule += "BISONTARGETS += " + _bison_targets + "\n";
    rule += _bison_targets + " &: " + string(argv[0]) + '\n';
    string  outtarget("$(patsubst %.y,%.cc,");
    outtarget += string(argv[0]) + ')';
    tmp = gmk_expand(outtarget.c_str());
    if (! tmp) {
      cerr << "Failed to expand " << outtarget << '\n';
      return 0;
    }
    outtarget = tmp;
    gmk_free(tmp);
    rule += "\tbison -d -o" + outtarget + " $<\n";
    gmk_floc floc = { __FILE__, __LINE__ };
    gmk_eval(rule.c_str(), &floc);
  }
  return 0;
}

