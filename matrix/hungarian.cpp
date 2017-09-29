#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
using namespace std;
typedef long long ll;

template <typename T>
T hungarian(const vector< vector<T> > &a, ll n) {
  ll p, q;
  vector<ll> fx(n, INF), fy(n, 0);
  vector<ll> x(n, -1), y(n, -1);

  REP(i, 0, n)
    REP(j, 0, n)
      fx[i] = max(fx[i], a[i][j]);

  for(ll i = 0; i < n;) {
    vector<ll> t(n, -1), s(n + 1, i);
    for(p = q = 0; p <= q && x[i] < 0; p++) {
      for(ll k = s[p], j = 0; j < n && x[i] < 0; j++) {
        if(fx[k] + fy[j] == a[k][j] && t[j] < 0) {
          s[++q] = y[j], t[j] = k;
          if(s[q] < 0)
            for(p = j; p >= 0; j = p)
              y[j] = k = t[j], p = x[k], x[k] = j;
        }
      }
    }
    if(x[i] < 0) {
      T d = INF;
      for(ll k = 0; k <= q; k++)
        for(ll j = 0; j < n; j++)
          if(t[j] < 0) d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
      for(ll j = 0; j < n; j++) fy[j] += (t[j] < 0 ? 0 : d);
      for(ll k = 0; k <= q; k++) fx[s[k]] -= d;
    } else ++i;
  }

  T ret = 0;
  REP(i, 0, n) ret += a[i][x[i]];

  return ret;
}

int main(void) {
  vector< vector<ll> > a(3, vector<ll>(3));
  a[0][0] = 5; a[0][1] = 3; a[0][2] = 8;
  a[1][0] = 3; a[1][1] = 2; a[1][2] = 4;
  a[2][0] = 7; a[2][1] = 9; a[2][2] = 5;
  cout << hungarian<ll>(a, 3) << endl; // 20
}
