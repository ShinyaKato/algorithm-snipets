#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;

/* calculate x ** d */
ll power_bigint(ll x, string const &d) {
  ll y = 1;
  ll n = d.size();
  for(ll i = d.size() - 1; i >= 0; i--) {
    ll c = d[i] - '0';
    ll z = 1;
    REP(j, 0, 10) {
      if(j == c) y = (y * z) % MOD;
      z = (z * x) % MOD;
    }
    x = z;
  }
  return y;
}

int main(void) {
  cout << power_bigint(123LL, "123456789012345678901234567890") << endl; // 124794765
}
