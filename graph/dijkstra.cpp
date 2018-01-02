#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
using namespace std;
typedef long long ll;

struct edge {
  ll v, dist;
};

struct state {
  ll v, cost;

  bool operator>(const state s) const {
    return cost > s.cost;
  }
};

vector<ll> dijkstra(vector< vector<edge> > &E, ll S) {
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

int main(void) {
  vector< vector<edge> > E(4);
  E[0].push_back((edge) { 1, 1 }); E[1].push_back((edge) { 0, 1 });
  E[0].push_back((edge) { 2, 5 }); E[2].push_back((edge) { 0, 5 });
  E[0].push_back((edge) { 3, 9 }); E[3].push_back((edge) { 0, 9 });
  E[1].push_back((edge) { 2, 2 }); E[2].push_back((edge) { 1, 2 });
  E[1].push_back((edge) { 3, 6 }); E[3].push_back((edge) { 1, 6 });
  E[2].push_back((edge) { 3, 3 }); E[3].push_back((edge) { 2, 3 });

  vector<ll> dp = dijkstra(E, 0);
  assert(dp.size() == E.size());
  assert(dp[0] == 0);
  assert(dp[1] == 1);
  assert(dp[2] == 3);
  assert(dp[3] == 6);
}
