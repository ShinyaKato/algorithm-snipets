class UnionFind {
private:
  vector<ll> data;

public:
  UnionFind(ll n): data(n, -1) {}

  ll size(ll i) { return -data[find(i)]; }
  bool root(ll i) { return data[i] < 0; }
  bool same(ll i, ll j) { return find(i) == find(j); }

  ll find(ll i) { return root(i) ? i : (data[i] = find(data[i])); }

  bool unite(ll i, ll j) {
    if(same(i, j)) return false;
    data[find(i)] += data[find(j)];
    data[find(j)] = find(i);
    return true;
  }
};
