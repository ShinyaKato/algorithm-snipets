#include <iostream>
#include <vector>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class LowestCommonAncestor {
public:
  ll vmax, lmax, *depth, **parent;
  vector<ll> *edge;

  LowestCommonAncestor(ll vmax): vmax(vmax) {
    ll p = 1;
    for(lmax = 1; p < vmax; lmax++) p *= 2;
    edge = new vector<ll>[vmax];
    depth = new ll[vmax];
    parent = new ll*[lmax];
    REP(i, 0, lmax) parent[i] = new ll[vmax];
  }

  void init(ll root) {
    dfs(root, -1, 0);
    REP(i, 0, lmax - 1) REP(j, 0, vmax) {
      parent[i + 1][j] = parent[i][j] >= 0 ? parent[i][parent[i][j]] : -1;
    }
  }

  ll query(ll u, ll v) {
    if(depth[u] > depth[v]) swap(u, v);
    REP(i, 0, lmax) if(((depth[v] - depth[u]) >> i) & 1) v = parent[i][v];
    if(u == v) return u;
    for(ll i = lmax - 1; i >= 0; i--) if(parent[i][u] != parent[i][v]) {
      u = parent[i][u];
      v = parent[i][v];
    }
    return parent[0][u];
  }

private:
  void dfs(ll v, ll p, ll d) {
    parent[0][v] = p;
    depth[v] = d;
    REP(i, 0, edge[v].size()) if(edge[v][i] != p) dfs(edge[v][i], v, d + 1);
  }
};

int main(void) {
  LowestCommonAncestor lca(5);
  lca.edge[0].push_back(1); lca.edge[1].push_back(0);
  lca.edge[1].push_back(2); lca.edge[2].push_back(1);
  lca.edge[1].push_back(3); lca.edge[3].push_back(1);
  lca.edge[0].push_back(4); lca.edge[4].push_back(0);
  lca.init(0);
  cout << lca.query(2, 3) << endl;
  cout << lca.query(1, 4) << endl;
  cout << lca.query(2, 4) << endl;
}
