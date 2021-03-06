#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

template <typename T> T hungarian(const vector< vector<T> > &a, ll n) {
  const ll INF = 1LL << 60;
  vector<ll> fx(n, INF), fy(n, 0), x(n, -1), y(n, -1);
  ll p, q;

  REP(i, 0, n) REP(j, 0, n) fx[i] = max(fx[i], a[i][j]);

  for(ll i = 0; i < n;) {
    vector<ll> t(n, -1), s(n + 1, i);
    for(p = q = 0; p <= q && x[i] < 0; p++) {
      for(ll k = s[p], j = 0; j < n && x[i] < 0; j++) {
        if(fx[k] + fy[j] == a[k][j] && t[j] < 0) {
          s[++q] = y[j], t[j] = k;
          if(s[q] < 0) for(p = j; p >= 0; j = p) y[j] = k = t[j], p = x[k], x[k] = j;
        }
      }
    }
    if(x[i] < 0) {
      T d = INF;
      REP(k, 0, q + 1) REP(j, 0, n) if(t[j] < 0) d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
      REP(j, 0, n) fy[j] += (t[j] < 0 ? 0 : d);
      REP(k, 0, q + 1) fx[s[k]] -= d;
    } else i++;
  }

  T ret = 0;
  REP(i, 0, n) ret += a[i][x[i]];

  return ret;
}

int main(void) {
  vector< vector<ll> > a = { { 5, 3, 8 }, { 3, 2, 4 }, { 7, 9, 5 } };
  assert(hungarian<ll>(a, 3) == 20);
}
