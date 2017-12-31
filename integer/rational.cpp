#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class rational {
  ll n, d;

  static ll gcd(ll a, ll b) { return b != 0 ? gcd(b, a % b) : a; }

public:
  rational(): n(0), d(1) {}
  rational(ll _n): n(_n), d(1) {}
  rational(ll _n, ll _d) {
    assert(_d != 0);
    ll g = gcd(abs(_n), abs(_d));
    n = _n / g * (_d / abs(_d));
    d = abs(_d) / g;
  }

  bool operator==(rational r) const { return n * r.d == d * r.n; }
  bool operator!=(rational r) const { return !(*this == r); }
  bool operator<(rational r) const { return n * r.d < d * r.n; }
  bool operator>(rational r) const { return n * r.d > d * r.n; }
  bool operator<=(rational r) const { return *this == r || *this < r; }
  bool operator>=(rational r) const { return *this == r || *this > r; }

  rational operator+(rational r) const { return rational(n * r.d + d * r.n, d * r.d); }
  rational operator-(rational r) const { return rational(n * r.d - d * r.n, d * r.d); }
  rational operator*(rational r) const { return rational(n * r.n, d * r.d); }
  rational operator/(rational r) const { return rational(n * r.d, d * r.n); }

  rational operator+=(const rational &r) { return *this = *this + r; }
  rational operator-=(const rational &r) { return *this = *this - r; }
  rational operator*=(const rational &r) { return *this = *this * r; }
  rational operator/=(const rational &r) { return *this = *this / r; }

  explicit operator double() const { return (double) n / d; }

  ll num() const { return n; }
  ll den() const { return d; }
};

int main(void) {
  assert(rational() == rational(0, 1));
  assert(rational(17) == rational(17, 1));
  assert(rational(50, 100) == rational(1, 2));

  assert(rational(1, 3) + rational(1, 2) == rational(5, 6));
  assert(rational(1, 3) - rational(1, 2) == rational(-1, 6));
  assert(rational(1, 3) * rational(1, 2) == rational(1, 6));
  assert(rational(1, 3) / rational(1, 2) == rational(2, 3));

  assert(rational(-50, 100) == rational(-1, 2));
  assert(rational(50, -100) == rational(-1, 2));
  assert(rational(-50, -100) == rational(1, 2));
  assert(rational(50, 100) - rational(50, 100) == rational(0, 1));
}
