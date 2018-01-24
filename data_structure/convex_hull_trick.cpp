#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

class ConvexHullTrick {
  vector<pll> deq;
  ll s, t;

public:
  ConvexHullTrick(ll n) { /* n: number of lines */
    deq.resize(n);
    s = 0, t = 0;
  }

  void add(ll a, ll b) { /* a must decrease monotonously */
    const pll p(a, b);
    while(s + 1 < t && check(deq[t - 2], deq[t - 1], p)) t--;
    deq[t++] = p;
  }

  ll query(ll x) { /* O(log n) */
    ll low = s - 1, high = t - 1;
    while(low + 1 < high) {
      ll mid = (low + high) / 2;
      if(isright(deq[mid], deq[mid + 1], x)) low = mid;
      else high = mid;
    }
    return f(deq[high], x);
  }

private:
  bool isright(const pll &p1, const pll &p2, ll x) {
    return (p1.second - p2.second) >= x * (p2.first - p1.first);
  }

  bool check(const pll &p1, const pll &p2, const pll &p3) {
    return (p2.first - p1.first) * (p3.second - p2.second) >= (p2.second - p1.second) * (p3.first - p2.first);
  }

  ll f(const pll &p, ll x) {
    return p.first * x + p.second;
  }
};

void test(ll N, ll *A, ll *B, ll *V) {
  ConvexHullTrick cht(N);
  REP(i, 0, N) cht.add(A[i], B[i]);
  REP(i, 0, N) assert(cht.query(i) == V[i]);
}

int main() {
  ll N1 = 3;
  ll A1[N1] = { 0, -2, -4 };
  ll B1[N1] = { 1, 4, 4 };
  ll V1[N1] = { 1, 1, -2 };
  test(N1, A1, B1, V1);

  ll N2 = 11;
  ll A2[N2] = {  0, -2, -4, -6, -8, -10, -12, -14, -16, -18, -20 };
  ll B2[N2] = { 1, 4, 8, 13, 19, 23, 21, 17, 14, 12, 11 };
  ll V2[N2] = { 1, 1, 0, -2, -6, -11, -26, -42, -60, -79, -99 };
  test(N2, A2, B2, V2);

  ll N3 = 12;
  ll A3[N3] = { 0, -2, -4, -6, -8, -10, -12, -14, -16, -18, -20, -22 };
  ll B3[N3] = { 10, 15, 66, 23, 28, 17, 18, 28, 38, 53, 39, 13 };
  ll V3[N3] = { 10, 10, 10, 7, -3, -13, -24, -36, -53, -75, -97, -119 };
  test(N3, A3, B3, V3);
}
