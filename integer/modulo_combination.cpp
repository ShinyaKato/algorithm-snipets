#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;

class ModuloCombination {
private:
  vector<ll> fact, inv_fact;

  static ll modulo_power(ll a, ll n) {
    if(n == 0) return 1;
    if(n % 2 == 0) return modulo_power((a * a) % MOD, n / 2);
    return (a * modulo_power(a, n - 1)) % MOD;
  }

public:
  ModuloCombination(ll N): fact(N + 1), inv_fact(N + 1) {
    fact[0] = 1;
    REP(i, 1, N + 1) fact[i] = (i * fact[i - 1]) % MOD;
    REP(i, 0, N + 1) inv_fact[i] = modulo_power(fact[i], MOD - 2);
  }

  ll operator()(ll n, ll r) {
    return fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD;
  }
};

class ModuloRangeSum {
private:
  vector<ll> acc;

public:
  ModuloRangeSum(const vector<ll> &vec): acc(vec.size() + 1, 0) {
    REP(i, 0, vec.size()) acc[i + 1] = (acc[i] + vec[i]) % MOD;
  }

  ll operator()(ll l, ll r) {
    return (acc[r + 1] - acc[l] + MOD) % MOD;
  }
};

int main(void) {
  ModuloCombination comb(200000);
  assert(comb(200000, 100000) == 879467333LL);
}
