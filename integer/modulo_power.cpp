#include <iostream>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;

ll modulo_power(ll a, ll n) {
  if(n == 0) return 1;
  if(n % 2 == 0) return modulo_power((a * a) % MOD, n / 2);
  return (a * modulo_power(a, n - 1)) % MOD;
}

int main(void) {
  cout << modulo_power(2, 10) << endl;                 // 1024
  cout << modulo_power(500, 10000000000000LL) << endl; // 166148332
}
