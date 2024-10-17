#include <iostream>
#include <string>

#include "dwm_gmk.h"

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_flex(const char *name, unsigned int argc, char *argv[])
{
  using namespace std;
  
  if ((argc == 1) && argv[0]) {
    std::string  rule;
    std::string  _flex_targets =
      "$(patsubst %.lex,%.cc," + string(argv[0]) + ')';
    char  *tmp = gmk_expand(_flex_targets.c_str());
    if (! tmp) {
      cerr << "Failed to expand " << _flex_targets << '\n';
      return 0;
    }
    _flex_targets = tmp;
    gmk_free(tmp);
    rule += "FLEXTARGETS += " + _flex_targets + "\n";
    rule += _flex_targets + ": " + string(argv[0]) + '\n';
    rule += "\tflex -o$@ $<\n";
    gmk_floc floc = { __FILE__, __LINE__ };
    gmk_eval(rule.c_str(), &floc);
  }
  return 0;
}

