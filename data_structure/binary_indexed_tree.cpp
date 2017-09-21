#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

/* 1-indexed, [1, n] */
template<typename T> class BinaryIndexedTree {
  vector<T> vec;
  const ll n;

public:
  BinaryIndexedTree(T _n) : vec(_n + 1), n(_n) {}

  T query(ll x) { /* query for [1, x] */
    T ret = 0;
    for(ll i = x; i > 0; i -= i & (-i)) ret += vec[i];
    return ret;
  }

  void update(ll x, T k) { /* update for [1, x] */
    for(ll i = x; i <= n; i += i & (-i)) vec[i] += k;
  }
};

int main(void) {
  BinaryIndexedTree<ll> bit(5);

  bit.update(3, 2);              // [0, 0, 2, 0, 0]
  cout << bit.query(2) << endl;  // 0
  cout << bit.query(3) << endl;  // 2
  bit.update(4, 5);              // [0, 0, 2, 5, 0]
  cout << bit.query(4) << endl;  // 7
  bit.update(1, 8);              // [8, 0, 2, 5, 0]
  cout << bit.query(3) << endl;  // 10
  cout << bit.query(5) << endl;  // 15
}
