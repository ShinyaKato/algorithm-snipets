#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1 << 28)
using namespace std;
typedef int ll;
typedef pair<ll, ll> pll;

class MinCostFlow {
public:
  struct edge { ll to, cap, cost, rev; };

private:
  ll V;
  vector< vector<edge> > G;
  vector<ll> h, dist, prevv, preve;

public:
  MinCostFlow(ll V): V(V), G(V), h(V, 0), dist(V), prevv(V), preve(V) {}

  void add_edge(ll from, ll to, ll cap, ll cost) {
    G[from].push_back((edge) { to, cap, cost, (ll) G[to].size() });
    G[to].push_back((edge) { from, 0, -cost, (ll) G[from].size() - 1 });
  }

  ll min_cost_flow(ll s, ll t, ll f) {
    ll ret = 0;
    while(f > 0) {
      priority_queue<pll, vector<pll>, greater<pll> > q;
      REP(i, 0, V) dist[i] = INF;
      dist[s] = 0;
      q.push(pll(0, s));
      while(!q.empty()) {
        pll p = q.top();
        q.pop();
        ll v = p.second;
        if(dist[v] < p.first) continue;
        REP(i, 0, G[v].size()) {
          edge &e = G[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            q.push(pll(dist[e.to], e.to));
          }
        }
      }
      if(dist[t] == INF) return -1;
      REP(v, 0, V) h[v] += dist[v];
      ll d = f;
      for(ll v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
      f -= d;
      ret += d * h[t];
      for(ll v = t; v != s; v = prevv[v]) {
        edge &e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return ret;
  }
};

int main(void) {
  MinCostFlow flow(5);
  flow.add_edge(0, 1, 10, 2);
  flow.add_edge(0, 2, 2, 4);
  flow.add_edge(1, 2, 6, 6);
  flow.add_edge(1, 3, 6, 2);
  flow.add_edge(2, 4, 5, 2);
  flow.add_edge(3, 2, 3, 3);
  flow.add_edge(3, 4, 8, 6);
  assert(flow.min_cost_flow(0, 4, 9));
}
