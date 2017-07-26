#include <iostream>
using namespace std;
typedef long long ll;

ll combination(int n, int r) {
  static ll comb[51][51];
  ll &ret = comb[n][r];
  if(ret != 0) return ret;
  if(n == 0 || r == 0) return ret = 1;
  if(n == r) return ret = 1;
  if(r == 1) return ret = n;
  return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}

int main(void) {
  cout << combination(4, 2) << endl;
  cout << combination(5, 2) << endl;
  cout << combination(10, 3) << endl;
  cout << combination(50, 25) << endl;

  return 0;
}
