#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
using namespace std;
typedef long long ll;

struct edge { ll to, cap, rev; };

vector<edge> G[100];
bool used[100];

void add_edge(ll from, ll to, ll cap) {
  G[from].push_back((edge) { to, cap, (ll) G[to].size() });
  G[to].push_back((edge) { from, 0, (ll) G[from].size() - 1 }); // Directed Graph
  // G[to].push_back((edge) { from, cap, (ll) G[from].size() - 1 }); // Undirected Graph
}

ll dfs(ll v, ll t, ll f) {
  if(v == t) return f;
  used[v] = true;
  REP(i, 0, G[v].size()) {
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0) {
      ll d = dfs(e.to, t, min(f, e.cap));
      if(d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

ll max_flow(ll s, ll t) {
  ll flow = 0;
  while(1) {
    memset(used, 0, sizeof(used));
    ll f = dfs(s, t, INF);
    if(f == 0 || f == INF) break;
    flow += f;
  }
  return flow;
}

int main(void) {
  add_edge(0, 1, 10);
  add_edge(0, 2, 1);
  add_edge(1, 2, 6);
  add_edge(1, 3, 6);
  add_edge(2, 4, 5);
  add_edge(3, 2, 3);
  add_edge(3, 4, 8);
  assert(max_flow(0, 4) == 11);
}
