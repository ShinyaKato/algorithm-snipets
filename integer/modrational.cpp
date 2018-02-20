#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;

class modratio {
  ll n, d;

public:
  modratio(): n(0), d(1) {}
  modratio(ll _n): n((_n + MOD) % MOD), d(1) {}
  modratio(ll _n, ll _d): n((_n + MOD) % MOD), d((_d + MOD) % MOD) {}

  modratio operator+(modratio r) const { return modratio(n * r.d + d * r.n, d * r.d); }
  modratio operator-(modratio r) const { return modratio(n * r.d - d * r.n, d * r.d); }
  modratio operator*(modratio r) const { return modratio(n * r.n, d * r.d); }
  modratio operator/(modratio r) const { return modratio(n * r.d, d * r.n); }

  ll num() const { return n; }
  ll den() const { return d; }

  ll value() const { // n * d^-1 % MOD
    ll t = MOD - 2, p = 1, q = d;
    while(t > 0) {
      if(t % 2) p = (p * q) % MOD;
      q = (q * q) % MOD;
      t /= 2;
    }
    return n * (p % MOD) % MOD;
  }
};

int main(void) {
  ll M = 26;
  modratio p = 0;
  REP(i, 1, M + 1) p = p + modratio(M - i) / modratio(M) / modratio(M);
  assert(p.value() == 711538467LL);
}
