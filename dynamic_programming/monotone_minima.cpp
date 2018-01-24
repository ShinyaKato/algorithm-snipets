#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
using namespace std;
typedef long long ll;

/* il, ir, jl, jr: [il, ir), [jl, jr)
 * f(i, j):
 *   arg(i) := f(i, j)のあるiを決めた時にf(i, _)に最小を与えるj
 *   j1 = arg(i1), j2 = arg(i2), i1 < i2ならばj1 <= j2
 */
void dfs(ll il, ll ir, ll jl, ll jr, function<ll(ll, ll)> &f, vector<ll> &ans) {
  if(il >= ir) return;

  ll im = (il + ir) / 2, jm;
  ans[im] = INF;
  REP(j, jl, jr) {
    ll v = f(im, j);
    if(ans[im] > v) {
      ans[im] = v;
      jm = j;
    }
  }

  dfs(il, im, jl, jm + 1, f, ans);
  dfs(im + 1, ir, jm, jr, f, ans);
}

int main() {
  ll N1 = 3;
  ll A1[N1] = { 1, 3, 2 };
  ll V1[N1] = { 1, 2, 2 };
  vector<ll> ans1(N1);
  function<ll(ll, ll)> f1 = [&](ll i, ll j) { return A1[j] + (i - j) * (i - j); };
  dfs(0, N1, 0, N1, f1, ans1);
  REP(i, 0, N1) assert(ans1[i] == V1[i]);

  ll N2 = 11;
  ll A2[N2] = { 1, 3, 6, 10, 15, 18, 15, 10, 6, 3, 1 };
  ll V2[N2] = { 1, 2, 4, 7, 10, 14, 10, 7, 4, 2, 1 };
  vector<ll> ans2(N2);
  function<ll(ll, ll)> f2 = [&](ll i, ll j) { return A2[j] + (i - j) * (i - j); };
  dfs(0, N2, 0, N2, f2, ans2);
  REP(i, 0, N2) assert(ans2[i] == V2[i]);

  ll N3 = 12;
  ll A3[N3] = { 10, 14, 64, 20, 24, 12, 12, 21, 30, 44, 29, 2 };
  ll V3[N3] = { 10, 11, 14, 16, 13, 12, 12, 13, 11, 6, 3, 2 };
  vector<ll> ans3(N3);
  function<ll(ll, ll)> f3 = [&](ll i, ll j) { return A3[j] + (i - j) * (i - j); };
  dfs(0, N3, 0, N3, f3, ans3);
  REP(i, 0, N3) assert(ans3[i] == V3[i]);
}
