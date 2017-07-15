#include <iostream>
#include <algorithm>
#define REP(i, a, n) for(int i = ((int) a); i < ((int) n); i++)
using namespace std;

template <class BI>
bool next_partial_permutation(BI first, BI middle, BI last) {
  reverse(middle, last);
  return next_permutation(first, last);
}

int main(void) {
  int a[5];
  REP(i, 0, 5) a[i] = i;
  do {
    REP(i, 0, 3) cout << a[i] << " ";
    cout << endl;
  } while(next_partial_permutation(a, a + 3, a + 5));

  return 0;
}
