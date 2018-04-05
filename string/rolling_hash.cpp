#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class RollingHash {
public:
  const ll B = 1009, MOD1 = 1000000007, MOD2 = 1000000009;

private:
  ll n;
  vector<ll> p1, p2, h1, h2;

public:
  RollingHash(const string &s): n(s.length()), p1(n + 1), p2(n + 1), h1(n + 1), h2(n + 1) {
    p1[0] = p2[0] = 1;
    REP(i, 0, n) p1[i + 1] = (p1[i] * B) % MOD1;
    REP(i, 0, n) p2[i + 1] = (p2[i] * B) % MOD2;
    h1[0] = h2[0] = 0;
    REP(i, 0, n) h1[i + 1] = (h1[i] * B + s[i]) % MOD1;
    REP(i, 0, n) h2[i + 1] = (h2[i] * B + s[i]) % MOD2;
  }

  ll hash(ll l, ll r) {
    ll x1 = (h1[r] - (h1[l] * p1[r - l] % MOD1) + MOD1) % MOD1;
    ll x2 = (h2[r] - (h2[l] * p2[r - l] % MOD2) + MOD2) % MOD2;
    return x1 * MOD2 + x2;
  }
};

int main(void) {
  string S1 = "afdsajfdsa";
  string S2 = "afdtajddsk";
  RollingHash rh1(S1), rh2(S2);

  REP(i1, 0, S1.size()) REP(j1, i1 + 1, S1.size() + 1) {
    REP(i2, 0, S2.size()) REP(j2, i2 + 1, S2.size() + 1) {
      string sub1 = S1.substr(i1, j1 - i1);
      string sub2 = S2.substr(i2, j2 - i2);
      ll h1 = rh1.hash(i1, j1);
      ll h2 = rh2.hash(i2, j2);
      cerr << "S1: " << sub1 << ", " << h1 << endl;
      cerr << "S2: " << sub2 << ": " << h2 << endl;
      if(sub1 == sub2) {
        assert(h1 == h2);
      } else {
        assert(h1 != h2);
      }
    }
  }
}
