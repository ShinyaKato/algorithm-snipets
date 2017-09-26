#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
#define MOD 1000000007LL
using namespace std;
typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

mat mul(mat &A, mat &B) {
  mat C(A.size(), vector<ll>(B[0].size()));
  REP(i, 0, A.size())
    REP(j, 0, B[0].size())
      REP(k, 0, B.size())
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
  return C;
}

mat pow(mat A, ll n) {
  mat B(A.size(), vec(A.size()));
  REP(i, 0, A.size()) B[i][i] = 1;
  while(n > 0) {
    if(n & 1) B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }
  return B;
}

int main(void) { // example of calculating n-the element of fibonacci mod 10^9 + 7
  mat A(2, vec(2));
  A[0][0] = 1; A[0][1] = 1;
  A[1][0] = 1; A[1][1] = 0;
  REP(i, 0, 20) cout << "fib(" << i << ") = " << pow(A, i)[1][0] << endl;
}
