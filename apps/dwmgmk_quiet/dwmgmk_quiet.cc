//===========================================================================
// @(#) $DwmPath$
//===========================================================================
//  Copyright (c) Daniel W. McRobb 2024
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//  3. The names of the authors and copyright holders may not be used to
//     endorse or promote products derived from this software without
//     specific prior written permission.
//
//  IN NO EVENT SHALL DANIEL W. MCROBB BE LIABLE TO ANY PARTY FOR
//  DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
//  INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE,
//  EVEN IF DANIEL W. MCROBB HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
//
//  THE SOFTWARE PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND
//  DANIEL W. MCROBB HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
//  UPDATES, ENHANCEMENTS, OR MODIFICATIONS. DANIEL W. MCROBB MAKES NO
//  REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER
//  IMPLIED OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE,
//  OR THAT THE USE OF THIS SOFTWARE WILL NOT INFRINGE ANY PATENT,
//  TRADEMARK OR OTHER RIGHTS.
//===========================================================================

//---------------------------------------------------------------------------
//!  \file dwmgmk_quiet.cc
//!  \author Daniel W. McRobb
//!  \brief NOT YET DOCUMENTED
//---------------------------------------------------------------------------

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static void Usage(const char *argv0)
{
  std::cerr << "Usage: " << argv0 << " message command [command_args...]\n";
  exit(1);
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static int GetCommandOutput(const std::string & msg, const std::string & cmd,
                            std::string & outstr)
{
  int  rc = 1;
  outstr.clear();
  FILE  *p = popen(cmd.c_str(), "r");
  if (p) {
    if (! msg.empty()) {
      std::cout << msg << '\n';
    }
    char    buf[256];
    while (fgets(buf, sizeof(buf), p)) {
      outstr += buf;
    }
    int  cmdexit = pclose(p);
    if (cmdexit == 0) {
      rc = 0;
    }
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  using namespace std;
  
  if (argc >= 3) {
    string  msg = argv[1];
    string  cmd;
    for_each(&argv[2], &argv[argc],
             [&] (auto arg) { cmd += arg; cmd += ' '; });
    if (! cmd.empty()) {
      string  outstr;
      if (GetCommandOutput(msg, cmd + "2>&1", outstr)) {
        cerr << cmd << '\n' << outstr;
        exit(1);
      }
      exit(0);
    }
    else {
      Usage(argv[0]);
    }
  }
  else {
    Usage(argv[0]);
  }
  exit(1);
}
