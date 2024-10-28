//===========================================================================
//  Copyright (c) Daniel W. McRobb 2024
//  All rights reserved.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//===========================================================================

//---------------------------------------------------------------------------
//!  \file dwm_gmk_flex.cc
//!  \author Daniel W. McRobb
//!  \brief dwm_gmk_bison GNU make extension function
//---------------------------------------------------------------------------

#include <iostream>
#include <map>
#include <regex>
#include <set>

#include "dwm_gmk.h"
#include "DwmGmkUtils.hh"

using namespace std;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static bool TargetFile(const std::string & arg,
                       pair<string,pair<string,string>> & tf)
{
  static const auto  rgxopts = regex::ECMAScript | regex::optimize;

  static const vector<pair<regex, pair<string, string>>> rgxs = {
    { regex("^(\\-o[ ]*)(.+)$", rgxopts),
      { "output", "-o " } },
    { regex("^(\\-\\-output=)(.+)$", rgxopts),
      { "output", "--output=" } },
    { regex("^(\\-\\-header-file=)(.+)$", rgxopts),
      { "header", "--header-file=" } },
    { regex("^(\\-\\-tables\\-file=)(.+)$", rgxopts),
      { "tables", "--tables-file=" } },
  };
  bool  rc = false;
  for (const auto & rgx : rgxs) {
    smatch  sm;
    if (regex_match(arg, sm, rgx.first)) {
      if (sm.size() == 3) {
        tf.first = rgx.second.first;
        tf.second.first = rgx.second.second;
        tf.second.second = sm[2].str();
        rc = true;
        break;
      }
    }
  }
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static void GetFlexArgs(int argc, char *argv[],
                        map<string,pair<string,string>> & targets,
                        set<string> & nontargets)
{
  targets.clear();
  nontargets.clear();
  regex  outfilergx("(^.+)\\..+$", regex::ECMAScript|regex::optimize);
  targets["output"] =
    pair<string,string>("-o ",regex_replace(argv[0], outfilergx, "$1.cc"));
  for (int i = 1; i < argc; ++i) {
    pair<string,pair<string,string>>  target;
    if (TargetFile(argv[i], target)) {
      targets[target.first] = target.second;
    }
    else {
      nontargets.insert(argv[i]);
    }
  }
  
  return;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static string FlexTargets(const map<string,pair<string,string>> & targets,
                          const set<string> & nontargets)
{
  std::string  targets_str;
  std::string  spc;
  for (const auto & target : targets) {
    targets_str += spc;
    targets_str += target.second.second;
    spc = " ";
  }
  return targets_str;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
char *dwm_gmk_flex(const char *name, unsigned int argc, char *argv[])
{
  char  *rule = 0;
  
  if ((argc >= 1) && argv[0]) {
    map<string,pair<string,string>> targets;
    set<string>        nontargets;
    GetFlexArgs(argc, argv, targets, nontargets);
    std::string  targets_str = FlexTargets(targets, nontargets);
    std::string  rulestr("FLEXTARGETS += " + targets_str + '\n');
    rulestr += targets_str + ": " + string(argv[0]) + '\n';
    string cmdstr("\t@dwmgmk_quiet \"Generating lexer from "
                  + Dwm::Gmk::RelPwd(argv[0]) + "\" ");
    cmdstr += "flex";
    if (! nontargets.empty()) {
      for (const auto & nontarget : nontargets) {
        cmdstr += ' ';
        cmdstr += nontarget;
      }
    }
    if (! targets.empty()) {
      for (const auto & target : targets) {
        cmdstr += ' ';
        cmdstr += target.second.first + target.second.second;
      }
    }
    cmdstr += " $<\n";
    rulestr += cmdstr;
    rule = Dwm::Gmk::GmkCopy(rulestr);
  }
  return rule;
}

