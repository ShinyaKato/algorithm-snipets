#include <bits/stdc++.h>
using namespace std;

class MaxFlow {
public:
  struct edge { int to, cap, rev; };

  const int INF = 1 << 28;
  int N;
  vector<vector<edge>> E;
  vector<int> level;
  vector<int> iter;

  MaxFlow(int N): N(N), E(N), level(N), iter(N) {}

  void add_directed_edge(int from, int to, int cap) {
    E[from].push_back((edge) { to, cap, (int) E[to].size() });
    E[to].push_back((edge) { from, 0, (int) E[from].size() - 1 });
  }

  void add_undirected_edge(int from, int to, int cap) {
    E[from].push_back((edge) { to, cap, (int) E[to].size() });
    E[to].push_back((edge) { from, cap, (int) E[from].size() - 1 });
  }

  void bfs(int s) {
    for (int i = 0; i < N; i++) level[i] = -1;
    level[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
      int v = q.front();
      q.pop();

      for (int i = 0; i < E[v].size(); i++) {
        edge &e = E[v][i];
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          q.push(e.to);
        }
      }
    }
  }

  int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < E[v].size(); i++) {
      edge &e = E[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
        int d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          E[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  int max_flow(int s, int t) {
    int flow = 0;
    while (1) {
      bfs(s);
      if (level[t] < 0) break;
      for (int i = 0; i < N; i++) iter[i] = 0;
      while (1) {
        int f = dfs(s, t, INF);
        if (f == 0 || f == INF) break;
        flow += f;
      }
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
