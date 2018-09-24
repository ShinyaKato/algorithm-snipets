#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class LowestCommonAncestor {
  ll N, D;
  vector<ll> depth;
  vector<vector<ll>> parent, E;

public:
  LowestCommonAncestor(ll N, ll D = 24): N(N), D(D) {
    depth.resize(N);
    parent.resize(D, vector<ll>(N));
    E.resize(N);
  }

  void add_edge(ll u, ll v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  void init(ll root) {
    dfs(root, -1, 0);
    REP(i, 0, D - 1) REP(j, 0, N) {
      if (parent[i][j] == -1) parent[i + 1][j] = -1;
      else parent[i + 1][j] = parent[i][parent[i][j]];
    }
  }

  ll query(ll u, ll v) {
    if (depth[u] > depth[v]) swap(u, v);
    REP(i, 0, D) {
      if ((depth[v] - depth[u]) & 1LL << i) {
        v = parent[i][v];
      }
    }
    if (u == v) return u;
    for (ll i = D - 1; i >= 0; i--) {
      if (parent[i][u] != parent[i][v]) {
        u = parent[i][u];
        v = parent[i][v];
      }
    }
    return parent[0][u];
  }

  ll dist(ll u, ll v) {
    return depth[u] + depth[v] - depth[query(u, v)] * 2;
  }

private:
  void dfs(ll v, ll p, ll d) {
    parent[0][v] = p;
    depth[v] = d;
    REP(i, 0, E[v].size()) {
      if (E[v][i] != p) {
        dfs(E[v][i], v, d + 1);
      }
    }
  }
};

/* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp */
int main(void) {
  ll N;
  cin >> N;
  LowestCommonAncestor lca(N);
  REP(i, 0, N) {
    ll k;
    cin >> k;
    REP(j, 0, k) {
      ll v;
      cin >> v;
      lca.add_edge(i, v);
    }
  }
  lca.init(0);

  ll Q;
  cin >> Q;
  REP(i, 0, Q) {
    ll U, V;
    cin >> U >> V;
    cout << lca.query(U, V) << endl;
  }
}
