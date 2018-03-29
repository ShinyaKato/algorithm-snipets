#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class MaxFlow {
public:
  struct edge { ll to, cap, rev; };

  const ll INF = 1LL << 60;
  ll N;
  vector< vector<edge> > E;
  vector<bool> used;

  MaxFlow(ll n): N(n), E(n), used(n) {};

  void add_directed_edge(ll from, ll to, ll cap) {
    E[from].push_back((edge) { to, cap, (ll) E[to].size() });
    E[to].push_back((edge) { from, 0, (ll) E[from].size() - 1 });
  }

  void add_undirected_edge(ll from, ll to, ll cap) {
    E[from].push_back((edge) { to, cap, (ll) E[to].size() });
    E[to].push_back((edge) { from, cap, (ll) E[from].size() - 1 });
  }

  ll dfs(ll v, ll t, ll f) {
    if(v == t) return f;
    used[v] = true;
    REP(i, 0, E[v].size()) {
      edge &e = E[v][i];
      if(!used[e.to] && e.cap > 0) {
        ll d = dfs(e.to, t, min(f, e.cap));
        if(d > 0) {
          e.cap -= d;
          E[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  ll max_flow(ll s, ll t) {
    ll flow = 0;
    while(1) {
      REP(i, 0, N) used[i] = false;
      ll f = dfs(s, t, INF);
      if(f == 0 || f == INF) break;
      flow += f;
    }
    return flow;
  }
};

int main(void) {
  MaxFlow flow(5);
  flow.add_directed_edge(0, 1, 10);
  flow.add_directed_edge(0, 2, 1);
  flow.add_directed_edge(1, 2, 6);
  flow.add_directed_edge(1, 3, 6);
  flow.add_directed_edge(2, 4, 5);
  flow.add_directed_edge(3, 2, 3);
  flow.add_directed_edge(3, 4, 8);
  assert(flow.max_flow(0, 4) == 11);
}
