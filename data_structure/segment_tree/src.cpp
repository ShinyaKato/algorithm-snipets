#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

/* 0-indexed, [0, n)
 *
 * requirements: let a, b, c in T
 *   op(op(a, b), c) = op(a, op(b, c))
 *   op(a, e) = op(e, a) = e
 */
template<typename T, typename E> class SegmentTree {
public:
  typedef function<T (T, T)> Operator;
  typedef function<T (T, E)> Apply;

  vector<T> data;
  ll n;        // size of elements (2^x alignment)
  T e;         // identity of monoid
  Operator op; // binary operator of monoid
  Apply apply; // apply effect to monoid

  // construct with size of elements
  SegmentTree(ll _n, T e, Operator op, Apply apply): e(e), op(op), apply(apply) {
    for(n = 1; n < _n; n *= 2);
    data.resize(n * 2 - 1, e);
  }

  // construct with initial values
  SegmentTree(const vector<T> &vec, T e, Operator op, Apply apply): e(e), op(op), apply(apply) {
    for(n = 1; n < vec.size(); n *= 2);
    data.resize(n * 2 - 1, e);
    REP(i, 0, vec.size()) data[i + n - 1] = vec[i];
    for(ll i = n - 2; i >= 0; i--) data[i] = op(data[i * 2 + 1], data[i * 2 + 2]);
  }

  // query for [a, b)
  T query(ll a, ll b) { return query(a, b, 0, 0, n); }
  T query(ll a, ll b, ll k, ll l, ll r) {
    if(r <= a || b <= l) return e;
    if(a <= l && r <= b) return data[k];
    T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    return op(vl, vr);
  }

  // update value at k
  void update(ll k, E x) {
    k += n - 1;
    data[k] = apply(data[k], x);
    while(k > 0) {
      k = (k - 1) / 2;
      data[k] = op(data[k * 2 + 1], data[k * 2 + 2]);
    }
  }
};

template<typename T, typename E>
ostream& operator<<(ostream& os, const SegmentTree<T, E>& segtree) {
  vector<ll> depth;
  vector<string> result;

  function<void (ll, ll, ll, ll)> dfs = [&](ll k, ll l, ll r, ll d) {
    if(k >= segtree.data.size()) return;
    dfs(k * 2 + 1, l, (l + r) / 2, d + 1);
    ostringstream stream;
    stream << " " << segtree.data[k] << " ";
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
  SegmentTree<ll, ll>::Operator op = [](ll a, ll b) { return a + b; };
  SegmentTree<ll, ll>::Apply apply = [](ll a, ll x) { return x; };
  SegmentTree<ll, ll> segtree(16, 0, op, apply);

  cerr << segtree << endl;

  segtree.update(0, 5); cerr << segtree << endl;
  segtree.update(1, 7); cerr << segtree << endl;
  segtree.update(2, 3); cerr << segtree << endl;
  segtree.update(3, 8); cerr << segtree << endl;
  assert(segtree.query(0, 4) == 23);
  assert(segtree.query(3, 4) == 8);
  assert(segtree.query(2, 4) == 11);
  assert(segtree.query(0, 2) == 12);
  assert(segtree.query(1, 2) == 7);

  segtree.update(2, 6); cerr << segtree << endl;
  segtree.update(5, 3); cerr << segtree << endl;
  segtree.update(6, 9); cerr << segtree << endl;
  segtree.update(7, 2); cerr << segtree << endl;
  assert(segtree.query(0, 8) == 40);
}
