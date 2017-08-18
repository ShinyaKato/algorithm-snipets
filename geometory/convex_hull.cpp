#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

struct P {
  double x, y;

  P() {}
  P(double x, double y): x(x), y(y) {}

  P operator+(P p) { return P(x + p.x, y + p.y); }
  P operator-(P p) { return P(x - p.x, y - p.y); }
  P operator*(P p) { return P(x - p.x, y - p.y); }

  double dot(P p) { return x * p.x + y * p.y; }
  double det(P p) { return x * p.y - y * p.x; }
};

vector<P> convex_hull(P *ps, ll n) {
  sort(ps, ps + n, [](const P &p, const P &q) {
    if(p.x != q.x) return p.x < q.x;
    return p.y < q.y;
  });
  ll k = 0;
  vector<P> qs(n * 2);

  REP(i, 0, n) {
    while(k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  for(ll i = n - 2, t = k; i >= 0; i--) {
    while(k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  qs.resize(k - 1);

  return qs; /* clockwise, first vertix is lexicographically smallest */
}

int main(void) {
  P p[6] = { P(0, 0), P(10, 0), P(0, 10), P(8, 8), P(3, 2), P(5, 1) };

  vector<P> v = convex_hull(p, 6); // (0, 0), (10, 0), (8, 8), (0, 10)
  REP(i, 0, v.size()) cout << v[i].x << " " << v[i].y << endl;
}
