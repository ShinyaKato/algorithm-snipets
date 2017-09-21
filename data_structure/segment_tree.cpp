#include <iostream>
#include <vector>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

/* 0-indexed, [0, n) */
template<typename T> class SegmentTree {
  vector<T> vec;
  ll n;          // size of vector
  T e;           // unity of monoid
  T (*op)(T, T); // binary operator of monoid

public:
  SegmentTree(ll _n, T _e, T (*_op)(T, T)) : e(_e), op(_op), n(1) {
    while(n < _n) n *= 2;
    vec.resize(n, e);
  }

  T query(ll a) { // query for a-th value
    return vec[a + n - 1];
  }

  T query(ll a, ll b) { // query for [a, b)
    return rquery(a, b, 0, 0, n);
  }

  void update(ll a, T k) { // update for a-th value
    a += n - 1;
    vec[a] = k;
    while(a > 0) {
      a = (a - 1) / 2;
      vec[a] = op(vec[a * 2 + 1], vec[a * 2 + 2]);
    }
  }

private:
  T rquery(ll a, ll b, ll k, ll l, ll r) {
    if(r <= a || b <= l) return e;
    if(a <= l && r <= b) return vec[k];
    T vl = rquery(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = rquery(a, b, k * 2 + 2, (l + r) / 2, r);
    return op(vl, vr);
  }
};

int main(void) {
  SegmentTree<ll> segtree(4, 1, [](ll a, ll b) { return a * b; });

  segtree.update(0, 5);
  segtree.update(1, 7);
  segtree.update(2, 3);
  segtree.update(3, 8);
  cout << segtree.query(0, 4) << endl; // 840
  cout << segtree.query(1, 3) << endl; // 21
  cout << segtree.query(2, 4) << endl; // 24
  cout << segtree.query(0, 2) << endl; // 35
  cout << segtree.query(0, 3) << endl; // 105
}
