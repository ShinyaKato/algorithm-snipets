#include <iostream>
#define REP(i, a, n) for(int i = ((int) a); i < ((int) n); i++)
#define MOD 1000000007
using namespace std;
typedef long long ll;

ll modulo_inverse(ll n) {
  ll t = MOD - 2, p = 1, q = n;
  while(t > 0) {
    if(t % 2) p = (p * q) % MOD;
    q = (q * q) % MOD;
    t /= 2;
  }
  return p % MOD;
}

int main(void) {
  REP(i, 1, 101) cout << i << " " << modulo_inverse(i) << " " << (i * modulo_inverse(i)) % MOD << endl;

  return 0;
}
