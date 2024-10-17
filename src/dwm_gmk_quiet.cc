#include "dwm_gmk.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_quiet(const char *name, unsigned int argc, char *argv[])
{
  using namespace std;

  if ((argc == 2) && argv[1]) {
    string  msg;
    if (argv[0]) {
      msg = argv[0];
    }
    string  cmd = argv[1];
    cmd += " 2>&1";
    FILE  *p = popen(cmd.c_str(), "r");
    if (p) {
      cout << msg << '\n';
      string  outstring;
      char    readbuf[256];
      while (fgets(readbuf, sizeof(readbuf), p) != nullptr) {
        outstring += readbuf;
      }
      int procexit = pclose(p);
      if (procexit) {
        cerr << argv[1] << '\n' << outstring;
        exit(1);
      }
    }
  }
  return 0;
}
