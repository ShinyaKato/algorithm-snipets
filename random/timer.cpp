#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class Timer {
  private:
    clock_t start;

  public:
    Timer() {
      start = clock();
    }

    double sec() {
      clock_t end = clock();
      return (double) (end - start) / CLOCKS_PER_SEC;
    }
};

