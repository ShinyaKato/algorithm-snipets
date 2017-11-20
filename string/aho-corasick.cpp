#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class PMA {
  PMA* next[256];
  vector<ll> matched;

  PMA() { REP(i, 0, 256) next[i] = NULL; }

  void build(vector<string> &p) {
    REP(i, 0, 256) next[i] = NULL;
    this->next[0] = this;
    REP(i, 0, p.size()) {
      PMA *now = this;
      REP(j, 0, p[i].length()) {
        if(now->next[p[i][j]] == 0) now->next[p[i][j]] = new PMA;
        now = now->next[p[i][j]];
      }
      now->matched.push_back(i);
    }

    queue<PMA*> q;
    REP(i, 1, 256) {
      if(!this->next[i]) this->next[i] = this;
      else {
        this->next[i]->next[0] = this;
        q.push(this->next[i]);
      }
    }

    while(!q.empty()) {
      PMA *now = q.front();
      q.pop();
      REP(i, 1, 256) if(now->next[i]){
        PMA *nxt = now->next[0];
        while(!nxt->next[i]) nxt = nxt->next[0];
        now->next[i]->next[0] = nxt->next[i];
        vector<ll> &m1 = now->next[i]->matched, &m2 = nxt->next[i]->matched;
        REP(j, 0, m2.size()) if(!binary_search(m1.begin(), m1.end(), m2[j])) m1.push_back(m2[j]);
        sort(m1.begin(), m1.end());
        q.push(now->next[i]);
      }
    }
  }

public:
  /* initialized by C-array of pattern string */
  PMA(string *parray, ll n) {
    vector<string> p;
    REP(i, 0, n) p.push_back(parray[i]);
    build(p);
  }

  /* initialized by vector of pattern string */
  PMA(vector<string> &p) {
    build(p);
  }

  /* find all substring mathing pattern */
  vector< vector<ll> > match(string s) {
    vector< vector<ll> > idx(s.length());
    PMA* pma = this;
    REP(i, 0, s.length()) {
      while(!pma->next[s[i]]) pma = pma->next[0];
      pma = pma->next[s[i]];
      for(ll j : pma->matched) idx[i].push_back(j);
    }
    return idx;
  }
};

int main(void) {
  string S[] = { "a", "b", "c", "ab", "abc", "bab" };

  PMA pma(S, sizeof(S) / sizeof(string));

  string T1 = "ababc";
  vector< vector<ll> > idx1 = pma.match(T1);
  REP(i, 0, idx1.size()) {
    cout << i << " (" << T1[i] << "): ";
    REP(j, 0, idx1[i].size()) cout << S[idx1[i][j]] << ", ";
    cout << endl;
  }

  string T2 = "axbcdkkqaxabxbc";
  vector< vector<ll> > idx2 = pma.match(T2);
  REP(i, 0, idx2.size()) {
    cout << i << " (" << T2[i] << "): ";
    REP(j, 0, idx2[i].size()) cout << S[idx2[i][j]] << ", ";
    cout << endl;
  }
}
