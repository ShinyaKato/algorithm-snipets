#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
using namespace std;
typedef long long ll;

/*
 * f(i, j)が満たすべき性質:
 *   arg(i) := f(i, j)のあるiを決めた時にf(i, _)に最小を与えるjとすると,
 *   j1 = arg(i1), j2 = arg(i2), i1 < i2ならばj1 <= j2 */
ll f(ll i, ll j) {
  ll A[12] = { 10, 14, 64, 20, 24, 12, 12, 21, 30, 44, 29, 2 };
  return A[j] + (i - j) * (i - j);
}

/* [il, ir), [jl, jr] */
void dfs(ll il, ll ir, ll jl, ll jr, vector<ll> &ans) {
  if(il >= ir) return;

  ll im = (il + ir) / 2, jm;
  ans[im] = INF;
  REP(j, jl, jr + 1) {
    ll v = f(im, j);
    if(ans[im] > v) {
      ans[im] = v;
      jm = j;
    }
  }

  dfs(il, im, jl, jm, ans);
  dfs(im + 1, ir, jm, jr, ans);
}

int main() {
  const ll N = 12;
  ll V[N] = { 10, 11, 14, 16, 13, 12, 12, 13, 11, 6, 3, 2 };
  vector<ll> ans(N);
  dfs(0, N, 0, N - 1, ans);
  REP(i, 0, N) assert(ans[i] == V[i]);
}
