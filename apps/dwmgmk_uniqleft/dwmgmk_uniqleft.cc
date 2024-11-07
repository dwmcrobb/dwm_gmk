#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static bool ToString(const vector<string> & v, string & s, char sep)
{
  s.clear();
  if (! v.empty()) {
    auto  it = v.cbegin();
    s += *it++;
    for ( ; it != v.cend(); ++it) {
      s += sep;
      s += *it;
    }
  }
  return (! s.empty());
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
static string UniqLeft(const vector<string> & v)
{
  string          rc;
  vector<string>  rv;
  set<string>     seen;
  for (const auto & word : v) {
    if (seen.find(word) == seen.end()) {
      seen.insert(word);
      rv.push_back(word);
    }
  }
  ToString(rv, rc, ' ');
  return rc;
}

//----------------------------------------------------------------------------
//!  
//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  vector<string>  v;
  for (int arg = 1; arg < argc; ++arg) {
    v.push_back(argv[arg]);
  }
  if (! v.empty()) {
    cout << UniqLeft(v) << '\n';
  }
  return 0;
}
