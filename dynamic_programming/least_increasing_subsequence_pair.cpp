#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define INF (1LL << 60)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

ll lis_rect(vector<pll> &rect) {
  ll N = rect.size();
  sort(rect.begin(), rect.end());

  ll dp[N];
  REP(i, 0, N) dp[i] = INF;
  REP(i, 0, N) *lower_bound(dp, dp + N, rect[i].second) = rect[i].second;

  return lower_bound(dp, dp + N, INF) - dp;
}

int main(void) {
  ll w[6] = { 10, 17, 92, 33, 34, 15 };
  ll h[6] = { 15, 21, 12, 71, 99, 14 };
  vector<pll> rect;
  REP(i, 0, 6) rect.push_back(pll(w[i], h[i]));

  cout << lis_rect(rect) << endl;
}
