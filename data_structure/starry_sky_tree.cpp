#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define LOWER_BOUND(a, v) lower_bound(a.begin(), a.end(), v) - a.begin()
#define UPPER_BOUND(a, v) upper_bound(a.begin(), a.end(), v) - a.begin()
using namespace std;
typedef int ll;

class StarrySkyTree {
  vector<ll> all, dat;
  ll n;

public:
  StarrySkyTree(ll _n) : n(1) {
    while(n < _n) n *= 2;
    all.resize(n * 2 - 1, 0);
    dat.resize(n * 2 - 1, 0);
  }

  ll minimum(ll a, ll b) { return minimum(a, b, 0, 0, n); }
  ll minimum(ll a, ll b, ll k, ll l, ll r) {
    if(r <= a || b <= l) return 0;
    if(a <= l && r <= b) return all[k] + dat[k];
    ll vl = minimum(a, b, k * 2 + 1, l, (l + r) / 2);
    ll vr = minimum(a, b, k * 2 + 2, (l + r) / 2, r);
    return min(vl, vr) + all[k];
  }

  void add(ll a, ll b, ll x) { add(a, b, x, 0, 0, n); }
  void add(ll a, ll b, ll x, ll k, ll l, ll r) {
    if(a <= l && r <= b) all[k] += x;
    else if(l < b && a < r) {
      add(a, b, x, k * 2 + 1, l, (l + r) / 2);
      add(a, b, x, k * 2 + 2, (l + r) / 2, r);
      dat[k] = min(all[k * 2 + 1] + dat[k * 2 + 1], all[k * 2 + 2] + dat[k * 2 + 2]);
    }
  }
};

int main(void) {
  StarrySkyTree starry(8);
  starry.add(0, 4, 1);
  
}
