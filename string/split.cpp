#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

vector<string> split(string s, string p) {
  vector<string> ret;
  ll h = 0;

  REP(i, 0, s.size() - p.size() + 1) if(s.substr(i, p.size()) == p) {
    ret.push_back(s.substr(h, i - h));
    h = i + p.size();
    i += (ll) p.size() - 1;
  }
  ret.push_back(s.substr(h, (ll) s.size() - h));

  return ret;
}

int main(void) {
  string s = "apple<!>banana<!>orange<!>potato<!><!>tomato<!><!><!>fish<!>";
  vector<string> sp = split(s, "<!>");

  assert(sp.size() == 10);
  string expect[] = { "apple", "banana", "orange", "potato", "", "tomato", "", "", "fish", "" };
  REP(i, 0, sp.size()) assert(sp[i] == expect[i]);
}
