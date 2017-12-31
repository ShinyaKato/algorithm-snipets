#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;

class modint {
  ll n;

public:
  modint(): n(0) {};
  modint(ll _n): n((_n + MOD) % MOD) {}
  modint(const modint &i): n(i.n) {}
  operator ll() const { return n; }

  modint operator+(const modint &i) const { return modint(n + i.n); }
  modint operator-(const modint &i) const { return modint(n - i.n); }
  modint operator*(const modint &i) const { return modint(n * i.n); }
  modint operator/(const modint &i) const { return modint(n * i.inverse().n); }

  modint operator+=(const modint &i) { return *this = *this + i; }
  modint operator-=(const modint &i) { return *this = *this - i; }
  modint operator*=(const modint &i) { return *this = *this * i; }
  modint operator/=(const modint &i) { return *this = *this / i; }

  modint inverse() const {
    modint p = 1, q = n;
    for(ll t = MOD - 2; t > 0; t /= 2) {
      if(t % 2) p *= q;
      q *= q;
    }
    return p;
  }
};

int main(void) {
  /* constructor */
  assert(modint() == 0LL);
  assert(modint(1000000008) == 1);
  assert(modint(modint(1000)) == 1000);

  /* logic */
  assert(modint(MOD + 100) == 100);
  assert(modint(MOD + 101) != 100);

  /* arithmetic */
  assert(modint(100000) + modint(1000000000) == 99993);
  assert(modint(100000) - modint(100001) == 1000000006);
  assert(modint(100000) * modint(100000) == 999999937);
  assert(modint(100000) / modint(2) == 50000);
  assert(modint(1000000000) * modint(1000000000) == 49);

  /* assignment */
  modint n1 = 100000; n1 += 1000000000; assert(n1 == 99993);
  modint n2 = 100000; n2 -= 100001; assert(n2 == 1000000006);
  modint n3 = 100000; n3 *= 100000; assert(n3 == 999999937);
  modint n4 = 100000; n4 /= 2; assert(n4 == 50000);
  assert(((modint(500) += modint(500)) * modint(1000)) == 1000000);

  /* inverse */
  assert(modint(123).inverse() == 886178868);
  assert(modint(334).inverse() == 2994012);

  /* cast */
  ll c1 = modint(1000000008); assert(c1 == 1);

  /* cout */
  stringstream out1; out1 << modint(1234567897) << endl; assert(out1.str() == "234567890\n");
}
