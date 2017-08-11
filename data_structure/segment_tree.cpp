#include <iostream>
#include <vector>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

template<typename T> class SegmentTree {
  ll n;
  T e;
  T (*op)(T, T);
  vector<T> dat;

public:
  SegmentTree(T _e, T (*_op)(T, T), ll _n) {
    e = _e;
    op = _op;
    n = 1;
    while(n < _n) n *= 2;
    REP(i, 0, 2 * n - 1) dat.push_back(e);
  }

  T query(ll a, ll b) {
    return rquery(a, b, 0, 0, n);
  }

  void update(ll k, T a) {
    k += n - 1;
    dat[k] = a;
    while(k > 0) {
      k = (k - 1) / 2;
      dat[k] = op(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

private:
  T rquery(ll a, ll b, ll k, ll l, ll r) {
    if(r <= a || b <= l) return e;
    if(a <= l && r <= b) return dat[k];
    T vl = rquery(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = rquery(a, b, k * 2 + 2, (l + r) / 2, r);
    return op(vl, vr);
  }
};

ll op(ll a, ll b) {
  return a * b;
}

int main(void) {
  SegmentTree<ll> segtree(1, op, 4);

  segtree.update(0, 5);
  segtree.update(1, 7);
  segtree.update(2, 3);
  segtree.update(3, 8);

  cout << segtree.query(0, 4) << endl;
  cout << segtree.query(1, 3) << endl;
  cout << segtree.query(2, 4) << endl;
  cout << segtree.query(0, 2) << endl;
  cout << segtree.query(0, 3) << endl;
}
