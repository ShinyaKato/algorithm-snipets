#include <iostream>
#include <vector>
#define REP(i, a, n) for(int i = ((int) a); i < ((int) n); i++)
using namespace std;

vector<string> split(string s, string p) {
  vector<string> ret;
  int h = 0;
  REP(i, 0, s.size() - p.size() + 1) if(s.substr(i, p.size()) == p) {
    ret.push_back(s.substr(h, i - h));
    h = i + p.size();
    i += (signed) p.size() - 1;
  }
  ret.push_back(s.substr(h, (signed) s.size() - h));
  return ret;
}

int main(void) {
  string s = "apple<!>banana<!>orange<!>potato<!><!>tomato<!><!><!>fish";
  vector<string> sp = split(s, "<!>");
  REP(i, 0, sp.size()) cout << sp[i] << endl;

  return 0;
}
