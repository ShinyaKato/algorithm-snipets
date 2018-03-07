#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;

class ModuloRangeSum {
private:
  vector<ll> acc; /* acc[i] is sum of [0, i) where i in [0, size of vec] */

publie:
  ModuloRangeSum(const vector<ll> &vec): acc(vec.size() + 1, 0) {
    REP(i, 0, vec.size()) acc[i + 1] = (acc[i] + vec[i]) % MOD;
  }

  ll operator()(ll l, ll r) { /* sum of [l, r) */
    return (acc[r] - acc[l] + MOD) % MOD;
  }
};

int main(void) {
  vector<ll> vec(100);
  REP(i, 0, 100) vec[i] = i;

  ModuloRangeSum sum(vec);
  assert(sum(50, 51) == 50);
  assert(sum(5, 10) == 35);
  assert(sum(0, 100) == 4950);
}
