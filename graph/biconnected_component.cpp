#include <bits/stdc++.h>
#define REP(i, a, n) for (ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class LowLink {
private:
  struct edge { ll to, id; };

public:
  ll N, M = 0;
  vector<vector<edge>> E;
  vector<ll> ord, low;
  vector<bool> visited, bridge;

  LowLink(ll N): N(N), E(N) {
    ord.resize(N);
    low.resize(N);
    visited.resize(N);
  }

  void add_edge(ll u, ll v) {
    E[u].push_back((edge) { v, M });
    E[v].push_back((edge) { u, M });
    M++;
  }

  vector<bool> search_bridge() {
    vector<bool> bridge(M);
    ll k = 0;
    dfs(0, -1, k, bridge);
    return bridge;
  }

private:
  void dfs(ll v, ll p, ll &k, vector<bool> &bridge) {
    visited[v] = true;
    ord[v] = low[v] = k++;
    for (edge &e : E[v]) if (e.to != p) {
      ll u = e.to;
      if (visited[u]) {
        low[v] = min(low[v], ord[u]);
      } else {
        dfs(u, v, k, bridge);
        low[v] = min(low[v], low[u]);
        if (ord[v] < low[u]) {
          bridge[e.id] = true;
        }
      }
    }
  }
};

class BiconnectedComponent {
private:
  struct edge { ll to, id; };

public:
  LowLink lowlink;
  ll N, M = 0;
  vector<vector<edge>> E;
  vector<ll> component;
  vector<bool> visited;

  BiconnectedComponent(ll N): N(N), lowlink(N) {
    E.resize(N);
    component.resize(N);
    visited.resize(N);
  }

  void add_edge(ll u, ll v) {
    lowlink.add_edge(u, v);
    E[u].push_back((edge) { v, M });
    E[v].push_back((edge) { u, M });
    M++;
  }

  ll decomposit() {
    vector<bool> bridge = lowlink.search_bridge();
    ll k = 0;
    REP(i, 0, N) if (!visited[i]) dfs(i, k++, bridge);
    return k;
  }

  void dfs(ll v, ll k, vector<bool> &bridge) {
    if (visited[v]) return;
    visited[v] = true;
    component[v] = k;
    for (edge &e : E[v]) if (!bridge[e.id]) dfs(e.to, k, bridge);
  }
};

int main(void) {
  BiconnectedComponent bc(7);

  bc.add_edge(0, 1);
  bc.add_edge(0, 5);
  bc.add_edge(1, 3);
  bc.add_edge(1, 4);
  bc.add_edge(3, 4);
  bc.add_edge(2, 5);
  bc.add_edge(2, 6);
  bc.add_edge(5, 6);

  assert(bc.decomposit() == 3);

  assert(bc.component[1] == bc.component[3]);
  assert(bc.component[1] == bc.component[4]);
  assert(bc.component[3] == bc.component[4]);

  assert(bc.component[2] == bc.component[5]);
  assert(bc.component[2] == bc.component[6]);
  assert(bc.component[5] == bc.component[6]);
}
