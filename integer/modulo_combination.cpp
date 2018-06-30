#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;

class ModuloCombination {
private:
  vector<ll> fact, fact_inv;

  static ll mod_pow(ll a, ll n) {
    if(n == 0) return 1;
    if(n % 2 == 0) return mod_pow((a * a) % MOD, n / 2);
    return (a * mod_pow(a, n - 1)) % MOD;
  }

public:
  ModuloCombination(ll N): fact(N + 1), fact_inv(N + 1) {
    fact[0] = 1;
    REP(i, 1, N + 1) fact[i] = (i * fact[i - 1]) % MOD;
    REP(i, 0, N + 1) fact_inv[i] = mod_pow(fact[i], MOD - 2);
  }

  ll operator()(ll n, ll r) {
    return fact[n] * fact_inv[r] % MOD * fact_inv[n - r] % MOD;
  }
};

int main(void) {
  ModuloCombination C(200000);
  assert(C(200000, 100000) == 879467333LL);
}
