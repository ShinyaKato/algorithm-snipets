#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class StronglyConnectedComponent {
public:
  const ll N;
  vector< vector<ll> > E, R;
  vector<ll> component;

  StronglyConnectedComponent(ll N): N(N), E(N), R(N), component(N) {}

  void add_edge(ll u, ll v) {
    E[u].push_back(v);
    R[v].push_back(u);
  }

  ll discomposit() {
    vector<ll> vs;
    vector<bool> used1(N, false);
    REP(i, 0, N) if(!used1[i]) dfs(i, vs, used1);

    vector<bool> used2(N, false);
    ll k = 0;
    for(ll i = vs.size() - 1; i >= 0; i--) if(!used2[vs[i]]) rdfs(vs[i], k++, used2);
    return k;
  }

private:
  void dfs(ll v, vector<ll> &vs, vector<bool> &used) {
    used[v] = true;
    REP(i, 0, E[v].size()) if(!used[E[v][i]]) dfs(E[v][i], vs, used);
    vs.push_back(v);
  }

  void rdfs(ll v, ll k, vector<bool> &used) {
    used[v] = true;
    component[v] = k;
    REP(i, 0, R[v].size()) if(!used[R[v][i]]) rdfs(R[v][i], k, used);
  }
};

int main(void) {
  StronglyConnectedComponent scc(12);

  vector<ll> u = { 0, 1, 1, 2, 3, 4, 4, 5, 6, 6, 6, 7, 8, 9, 9, 10 };
  vector<ll> v = { 1, 2, 3, 4, 2, 3, 5, 6, 7, 8, 9, 5, 10, 8, 11, 8 };
  REP(i, 0, u.size()) scc.add_edge(u[i], v[i]);

  ll k = scc.discomposit();

  vector< vector<ll> > cmp = { { 0 }, { 1 }, { 2, 3, 4 }, { 5, 6, 7 }, { 8, 10 }, { 9 }, { 11 } };
  assert(k == cmp.size());
  REP(i, 0, cmp.size()) {
    REP(j, 0, cmp[i].size()) {
      ll p = cmp[i][j], q = cmp[i][(j + 1) % cmp[i].size()];
      assert(scc.component[p] == scc.component[q]);
    }
  }
}
