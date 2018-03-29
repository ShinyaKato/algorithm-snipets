#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class Dijkstra {
public:
  struct edge { ll v, dist; };

  struct state {
    ll v, cost;
    bool operator>(const state s) const { return cost > s.cost; }
  };

  const ll INF = (1LL << 60);
  ll N;
  vector< vector<edge> > E;

  Dijkstra(ll n): N(n), E(n) {}

  void add_directed_edge(ll u, ll v, ll d) {
    E[u].push_back((edge) { v, d });
  }

  void add_undirected_edge(ll u, ll v, ll d) {
    E[u].push_back((edge) { v, d });
    E[v].push_back((edge) { u, d });
  }

  vector<ll> shortest_path(ll S) {
    vector<ll> dp(E.size(), INF);
    priority_queue<state, vector<state>, greater<state> > q;
    q.push((state) { S, 0 });
    while(!q.empty()) {
      ll v = q.top().v, cost = q.top().cost;
      q.pop();
      if(dp[v] <= cost) continue;
      dp[v] = cost;
      REP(i, 0, E[v].size()) {
        ll nv = E[v][i].v, ncost = cost + E[v][i].dist;
        if(dp[nv] > ncost) q.push((state) { nv, ncost });
      }
    }
    return dp;
  }
};

int main(void) {
  Dijkstra dijkstra(4);
  dijkstra.add_undirected_edge(0, 1, 1);
  dijkstra.add_undirected_edge(0, 2, 5);
  dijkstra.add_undirected_edge(0, 3, 9);
  dijkstra.add_undirected_edge(1, 2, 2);
  dijkstra.add_undirected_edge(1, 3, 6);
  dijkstra.add_undirected_edge(2, 3, 3);

  vector<ll> dp = dijkstra.shortest_path(0);
  assert(dp.size() == 4);
  assert(dp[0] == 0);
  assert(dp[1] == 1);
  assert(dp[2] == 3);
  assert(dp[3] == 6);
}
