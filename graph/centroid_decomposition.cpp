#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

struct edge {
  ll to;
  /* add other attributes of a edge. */
};
typedef vector< vector<edge> > graph;

ll tree_size(ll v, ll p, graph &E, vector<bool> &dead) {
  ll sum = 1;
  for(edge e : E[v]) if(e.to != p && !dead[e.to]) sum += tree_size(e.to, v, E, dead);
  return sum;
};

pll centroid(ll v, ll p, ll n, graph &E, vector<bool> &dead) {
  bool ok = true;
  ll cnt = 1;
  for(edge e : E[v]) if(e.to != p && !dead[e.to]) {
    pll r = centroid(e.to, v, n, E, dead);
    if(r.first >= 0) return r;
    ok = ok && (r.second <= n / 2);
    cnt += r.second;
  }
  ok = ok && (n - cnt <= n / 2);
  return pll(ok ? v : -1, cnt);
};

/* template of centroid decomposition */
void subtree(ll v, graph &E, vector<bool> &dead) {
  ll n = tree_size(v, -1, E, dead);
  ll c = centroid(v, -1, n, E, dead).first;
  dead[c] = true;

  for(edge e : E[c]) if(!dead[e.to]) subtree(e.to, E, dead);

  /* compute something about whole of the tree. */
  /* compute something using result of subtrees decomposited by centroid. */

  dead[c] = false;
}

int main(void) {
}
