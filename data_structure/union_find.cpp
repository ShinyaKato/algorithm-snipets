#include <iostream>
#include <vector>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class UnionFind {
  vector<ll> a;

public:
  UnionFind(ll n) {
    REP(i, 0, n) a.push_back(-1);
  }

  ll find(ll i) {
    return a[i] < 0 ? i : (a[i] = find(a[i]));
  }

  bool unite(ll parent, ll child) {
    if(find(child) == find(parent)) return false;
    a[find(parent)] += a[find(child)];
    a[find(child)] = find(parent);
    return true;
  }

  ll size(ll i) {
    return -a[find(i)];
  }

  bool root(ll i) {
    return i == find(i);
  }

  bool same(ll i, ll j) {
    return find(i) == find(j);
  }
};

int main(void) {
  UnionFind uf(5);
  uf.unite(1, 2);
  uf.unite(0, 4);
  REP(i, 0, 5) cout << uf.find(i) << " " << uf.size(i) << endl; // 0, 1, 1, 3, 0

  return 0;
}
