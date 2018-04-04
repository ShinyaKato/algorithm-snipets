#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

vector<ll> suffix_array(const string &S) {
  ll n = S.length(), k = 1;
  vector<ll> sa(n + 1), rnk(n + 1), tmp(n + 1);

  auto compare_sa = [&](const ll& i, const ll& j) {
    if(rnk[i] != rnk[j]) return rnk[i] < rnk[j];
    ll ri = i + k <= n ? rnk[i + k] : -1;
    ll rj = j + k <= n ? rnk[j + k] : -1;
    return ri < rj;
  };

  REP(i, 0, n + 1) sa[i] = i;
  REP(i, 0, n + 1) rnk[i] = i < n ? S[i] : -1;

  for(; k <= n; k *= 2) {
    sort(sa.begin(), sa.end(), compare_sa);
    tmp[sa[0]] = 0;
    REP(i, 1, n + 1) tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
    REP(i, 0, n + 1) rnk[i] = tmp[i];
  }

  return sa;
}

int main(void) {
  string S = "abracadabra";
  vector<ll> sa = suffix_array(S);

  vector<ll> expected = { 11, 10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2 };
  assert(sa.size() == expected.size());
  REP(i, 0, sa.size()) assert(sa[i] == expected[i]);

  REP(i, 1, sa.size()) cout << S.substr(sa[i], S.length() - sa[i]) << endl;
}
