#include <bits/stdc++.h>
#define REP(i, a, n) for (ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

class XorShift {
private:
  unsigned int x, y, z, w;

public:
  static constexpr unsigned int min() { return 0u; };
  static constexpr unsigned int max() { return UINT_MAX; };

  XorShift() {
    init();
  }

  void init() {
    init_with_seed(0);
  }

  void init_with_random_seed() {
    random_device rd;
    init_with_seed(rd());
  }

  void init_with_seed(int seed) {
    x = 123456789u, y = 362436069u, z = 521288629u, w = 88675123 + seed;
  }

  unsigned int random() {
    unsigned int t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }

  double uniform() {
    return (double) random() / max();
  }

  unsigned int range(unsigned int l, unsigned int r) {
    return random() % (r - l) + l;
  }

  int negative_or_positive() {
    return ((int) range(0, 2)) * 2 - 1;
  }
};

int main(void) {
  XorShift xorshift;
}
