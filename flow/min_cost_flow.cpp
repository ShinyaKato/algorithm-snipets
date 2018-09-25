#include <bits/stdc++.h>
using namespace std;

class MinCostFlow {
public:
  struct edge { int to, cap, cost, rev; };

private:
  const int INF = 1 << 28;
  int N;
  vector<vector<edge>> E;
  vector<int> h, dist, prevv, preve;

public:
  MinCostFlow(int N): N(N), E(N), h(N, 0), dist(N), prevv(N), preve(N) {}

  void add_directed_edge(int from, int to, int cap, int cost) {
    E[from].push_back((edge) { to, cap, cost, (int) E[to].size() });
    E[to].push_back((edge) { from, 0, -cost, (int) E[from].size() - 1 });
  }

  int min_cost_flow(int s, int t, int f) {
    int ret = 0;
    while (f > 0) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
      for (int i = 0; i < N; i++) dist[i] = INF;
      dist[s] = 0;
      q.push(make_pair(0, s));
      while (!q.empty()) {
        pair<int, int> p = q.top();
        q.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (int i = 0; i < E[v].size(); i++) {
          edge &e = E[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            q.push(make_pair(dist[e.to], e.to));
          }
        }
      }
      if (dist[t] == INF) return -1;
      for (int v = 0; v < N; v++) h[v] += dist[v];
      int d = f;
      for (int v = t; v != s; v = prevv[v]) d = min(d, E[prevv[v]][preve[v]].cap);
      f -= d;
      ret += d * h[t];
      for (int v = t; v != s; v = prevv[v]) {
        edge &e = E[prevv[v]][preve[v]];
        e.cap -= d;
        E[v][e.rev].cap += d;
      }
    }
    return ret;
  }
};

int main(void) {
  MinCostFlow flow(5);
  flow.add_directed_edge(0, 1, 10, 2);
  flow.add_directed_edge(0, 2, 2, 4);
  flow.add_directed_edge(1, 2, 6, 6);
  flow.add_directed_edge(1, 3, 6, 2);
  flow.add_directed_edge(2, 4, 5, 2);
  flow.add_directed_edge(3, 2, 3, 3);
  flow.add_directed_edge(3, 4, 8, 6);
  assert(flow.min_cost_flow(0, 4, 9));
}
