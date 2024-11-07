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
static string UniqRight(const vector<string> & v)
{
  string          rc;
  vector<string>  rv;
  set<string>     seen;
  for (auto it = v.crbegin(); it != v.crend(); ++it) {
    if (seen.find(*it) == seen.end()) {
      seen.insert(*it);
      rv.push_back(*it);
    }
  }
  std::reverse(rv.begin(), rv.end());
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
    cout << UniqRight(v) << '\n';
  }
  return 0;
}
