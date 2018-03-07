#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

/* 0-indexed, [0, n)
 *
 * requirements:
 * let a, b, c in T, x, y, z in E
 *   op(op(a, b), c) = op(a, op(b, c))
 *   op(a, e) = op(e, a) = e
 *   merge(merge(x, y), z) = merge(x, merge(y, z))
 *   merge(x, d) = merge(d, x) = d
 *   apply(apply(a, x), y) = apply(a, merge(x, y))
 *   apply(a, d) = a
 */
template<typename T, typename E> class LazySegmentTree {
public:
  typedef function<T (T, T)> Operator;
  typedef function<E (E, E)> Merge;
  typedef function<T (T, E)> Apply;
  typedef function<E (E, ll)> Product;

  vector<T> data;
  vector<E> lazy;
  ll n;        // size of elements (2^x alignment)
  T e;         // identity of monoid
  Operator op; // binary operator of monoid
  E d;         // identity of effect
  Merge merge; // merge effects
  Apply apply; // apply effect to monoid
  Product p;   // calculate effect * n

  // construction with size of elements
  LazySegmentTree(ll _n, T e, Operator op, E d, Merge merge, Apply apply, Product p):
    e(e), op(op), d(d), merge(merge), apply(apply), p(p) {
    for(n = 1; n < _n; n *= 2);
    data.resize(n * 2 - 1, e);
    lazy.resize(n * 2 - 1, d);
  }

  // construction with initial values
  LazySegmentTree(const vector<T> &vec, T e, Operator op, E d, Merge merge, Apply apply, Product p):
    e(e), op(op), d(d), merge(merge), apply(apply), p(p) {
    for(n = 1; n < (ll) vec.size(); n *= 2);
    data.resize(n * 2 - 1, e);
    lazy.resize(n * 2 - 1, d);
    REP(i, 0, vec.size()) data[i + n - 1] = vec[i];
    for(ll i = n - 2; i >= 0; i--) data[i] = op(data[i * 2 + 1], data[i * 2 + 2]);
  }

  // evaluate lazy update
  void eval(ll k, ll l, ll r) {
    if(r - l > 1) {
      lazy[k * 2 + 1] = merge(lazy[k * 2 + 1], lazy[k]);
      lazy[k * 2 + 2] = merge(lazy[k * 2 + 2], lazy[k]);
    }
    data[k] = apply(data[k], p(lazy[k], r - l));
    lazy[k] = d;
  }

  // query for [a, b)
  T query(ll a, ll b) { return query(a, b, 0, 0, n); }
  T query(ll a, ll b, ll k, ll l, ll r) {
    eval(k, l, r);
    if(r <= a || b <= l) return e;
    if(a <= l && r <= b) return data[k];
    T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    return op(vl, vr);
  }

  // update values of [a, b)
  T update(ll a, ll b, E x) { return update(a, b, x, 0, 0, n); }
  T update(ll a, ll b, E x, ll k, ll l, ll r) {
    eval(k, l, r);
    if(r <= a || b <= l) return data[k];
    if(a <= l && r <= b) {
      lazy[k] = merge(lazy[k], x);
      return apply(data[k], p(lazy[k], r - l));
    }
    T vl = update(a, b, x, k * 2 + 1, l, (l + r) / 2);
    T vr = update(a, b, x, k * 2 + 2, (l + r) / 2, r);
    return data[k] = op(vl, vr);
  }
};

template<typename T, typename E>
ostream& operator<<(ostream& os, const LazySegmentTree<T, E>& segtree) {
  vector<ll> depth;
  vector<string> result;

  function<void (ll, ll, ll, ll)> dfs = [&](ll k, ll l, ll r, ll d) {
    if(k >= segtree.data.size()) return;
    T data = segtree.data[k];
    E lazy = segtree.lazy[k];
    T v = segtree.apply(data, segtree.p(lazy, r - l));
    ostringstream stream;
    stream << " (" << v << ", " << data << ", " << lazy << ") ";
    dfs(k * 2 + 1, l, (l + r) / 2, d + 1);
    depth.push_back(d);
    result.push_back(stream.str());
    dfs(k * 2 + 2, (l + r) / 2, r, d + 1);
  };
  dfs(0, 0, segtree.n, 0);

  ll maxd = 0;
  REP(i, 0, depth.size()) maxd = max(maxd, depth[i] + 1);
  vector<ll> len(maxd, 0);
  REP(i, 0, result.size()) len[depth[i]] = max(len[depth[i]], (ll) result[i].size());

  ll idxlen = 0;
  vector<string> idx;
  REP(i, 0, result.size()) if(i % 2 == 0) {
    string s = " #" + to_string(i / 2) + " ";
    idx.push_back(s);
    idxlen = max(idxlen, (ll) s.size());
  }

  vector<string> blank(len.size(), ""), line(len.size(), "");
  REP(i, 0, len.size()) REP(j, 0, len[i]) blank[i] += " ";
  REP(i, 0, len.size()) REP(j, 0, len[i]) line[i] += "-";
  REP(i, 0, result.size()) REP(j, result[i].size(), len[depth[i]]) result[i] += " ";
  REP(i, 0, idx.size()) REP(j, idx[i].size(), idxlen) idx[i] += " ";
  string idxline = "";
  REP(i, 0, idxlen) idxline += "-";

  os << "SegmentTree: size = " << segtree.n << endl;
  os << "+";
  REP(i, 0, maxd) os << line[i] << "+";
  os << idxline << "+" << endl;
  REP(i, 0, result.size()) {
    os << "|";
    REP(j, 0, depth[i]) os << blank[j] << "|";
    os << result[i] << (depth[i] + 1 != maxd ? "+" : "|");
    REP(j, depth[i] + 1, maxd) os << line[j] << "+";
    if(i % 2 == 0) os << idx[i / 2] << "|";
    else os << idxline << "+";
    os << endl;
  }
  os << "+";
  REP(i, 0, maxd) os << line[i] << "+";
  os << idxline << "+";

  return os;
}

int main(void) {
  const ll INF = (1LL << 28);
  const ll N = 8, Q = 13;
  vector<ll> A = { 10, 0, 4, 4, 7, 2, 5, 9 };
  vector<ll> T = { 1, 2, 1, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1 };
  vector<ll> L = { 6, 0, 4, 5, 5, 6, 5, 1, 1, 5, 7, 3, 4 };
  vector<ll> R = { 8, 3, 6, 6, 6, 8, 8, 6, 5, 8, 8, 8, 6 };
  vector<ll> X = { 0, 0, 0, -7, 0, 0, -4, 9, 0, 4, 0, -1, 0 };
  vector<ll> Z = { 5, 0, 2, 0, -5, 5, 0, 0, 9, 0, 9, 0, 3 };

  LazySegmentTree<ll, ll>::Operator op = [](ll a, ll b) { return min(a, b); };
  LazySegmentTree<ll, ll>::Merge merge = [](ll x, ll y) { return x + y; };
  LazySegmentTree<ll, ll>::Apply apply = [](ll a, ll x) { return a + x; };
  LazySegmentTree<ll, ll>::Product p = [](ll x, ll n) { return x; };
  LazySegmentTree<ll, ll> segtree(A, INF, op, 0, merge, apply, p);

  cerr << segtree.n << endl;
  REP(i, 0, Q) {
    if(T[i] == 1) {
      assert(segtree.query(L[i], R[i]) == Z[i]);
      cerr << segtree << endl;
    }
    if(T[i] == 2) {
      segtree.update(L[i], R[i], X[i]);
    }
  }
}
