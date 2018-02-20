#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

struct edge { ll v, d; };

/* initialization of d
 *   1. find shortest path from s: d[i] = INF, d[s] = 0
 *   2. find negative loop:        d[i] = 0
 */
bool bellmanford(vector< vector<edge> > &E, vector<ll> &d) {
  bool updated;
  REP(k, 0, E.size()) {
    updated = false;
    REP(u, 0, E.size()) for(edge e : E[u]) if(d[e.v] > d[u] + e.d) {
      d[e.v] = d[u] + e.d;
      updated = true;
    }
  }
  return updated;
}

/* shortest path from s */
vector<ll> shortest_path(vector< vector< edge> > &E, ll s) {
  vector<ll> d(E.size(), INF);
  d[s] = 0;
  bellmanford(E, d);
  return d;
}

/* negative loop */
bool find_negative_loop(vector< vector<edge> > &E) {
  vector<ll> d(E.size(), 0);
  return bellmanford(E, d);
}

int main(void) {
  
}
