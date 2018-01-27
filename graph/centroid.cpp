#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
using namespace std;
typedef long long ll;

vector<ll> centroid(vector< vector<ll> > &E) {
  ll N = E.size();
  vector<ll> cnt(N);
  vector<ll> c;
  function<void (ll, ll)> dfs = [&](ll v, ll p) {
    bool ok = true;
    cnt[v] = 1;
    for(ll u : E[v]) if(u != p) {
      dfs(u, v);
      ok = ok && (cnt[u] <= N / 2);
      cnt[v] += cnt[u];
    }
    ok = ok && (N - cnt[v] <= N / 2);
    if(ok) c.push_back(v);
  };
  dfs(0, -1);
  return c;
}

vector<ll> centroid_with_dead(vector< vector<ll> > &E, ll v, vector<bool> &dead) {
  function<ll (ll, ll)> subtree_size = [&](ll v, ll p) {
    ll sum = 1;
    for(ll u : E[v]) if(u != p && !dead[u]) sum += subtree_size(u, v);
    return sum;
  };
  ll N = subtree_size(v, -1);
  vector<ll> cnt(E.size());
  vector<ll> c;
  function<void (ll, ll)> dfs = [&](ll v, ll p) {
    bool ok = true;
    cnt[v] = 1;
    for(ll u : E[v]) if(u != p && !dead[u]) {
      dfs(u, v);
      ok = ok && (cnt[u] <= N / 2);
      cnt[v] += cnt[u];
    }
    ok = ok && (N - cnt[v] <= N / 2);
    if(ok) c.push_back(v);
  };
  dfs(v, -1);
  return c;
}

int main(void) {
  vector< vector<ll> > E1 { { 1, 2, 3, 5 }, { 0 }, { 0 }, { 0, 4 }, { 3 }, { 0, 6, 7 }, { 5 }, { 5 } };
  vector<ll> ret1 = centroid(E1);
  assert(ret1.size() == 1);
  assert(ret1[0] == 0);

  vector< vector<ll> > E2 { { 1 }, { 0, 2 }, { 1, 3 }, { 2, 4 }, { 3, 5, 6, 7 }, { 4 }, { 4 }, { 4 } };
  vector<ll> ret2 = centroid(E2);
  assert(ret2.size() == 2);
  sort(ret2.begin(), ret2.end());
  assert(ret2[0] == 3);
  assert(ret2[1] == 4);
}
