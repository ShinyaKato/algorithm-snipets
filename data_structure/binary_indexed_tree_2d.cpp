#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

/* 1-indexed, [(1, 1), (m, n)] */
template<typename T> class BinaryIndexedTree2D {
  vector< vector<ll> > vec;
  const ll m, n;

public:
  BinaryIndexedTree2D(ll _m, ll _n) : vec(_m + 1, vector<T>(_n + 1)), m(_m), n(_n) {}

  T query(ll y, ll x) { /* query for [(1, 1), (y, x)] */
    T ret = 0;
    for(ll i = y; i > 0; i -= i & (-i))
      for(ll j = x; j > 0; j -= j & (-j))
        ret += vec[i][j];
    return ret;
  }

  void update(ll y, ll x, T k) { /* update for [(1, 1,), (y, x)] */
    for(ll i = y; i <= m; i += i & (-i))
      for(ll j = x; j <= n; j += j & (-j))
        vec[i][j] += k;
  }
};

int main(void) {
  BinaryIndexedTree2D<ll> bit(5, 4);

  REP(i, 0, 5) REP(j, 0, 4) bit.update(i + 1, j + 1, i * j);
  cout << bit.query(3, 3) << endl; //  9
  cout << bit.query(5, 4) << endl; // 60
  bit.update(3, 4, -6);
  cout << bit.query(5, 4) << endl; // 54
}
