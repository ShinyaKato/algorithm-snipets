#include <iostream>
#define REP(i, a, n) for(int i = ((int) a); i < ((int) n); i++)
using namespace std;

template<typename FI>
void parted_rotate(FI first1, FI last1, FI first2, FI last2) {
  if(first1 == last1 || first2 == last2) return;
  FI next = first2;
  while(first1 != next) {
    std::iter_swap(first1++, next++);
    if(first1 == last1) first1 = first2;
    if(next == last2) next = first2;
    else if(first1 == first2) first2 = next;
  }
}

template<typename BI>
bool next_combination_imp(BI first1, BI last1, BI first2, BI last2) {
  if(first1 == last1 || first2 == last2) return false;
  BI target = last1; --target;
  BI last_elem = last2; --last_elem;
  while(target != first1 && !(*target < *last_elem)) --target;
  if(target == first1 && !(*target < *last_elem)) {
    parted_rotate(first1, last1, first2, last2);
    return false;
  }
  BI next = first2;
  while(!(*target < *next)) ++next;
  std::iter_swap(target++, next++);
  parted_rotate(target, last1, next, last2);
  return true;
}

template<typename BI>
inline bool next_combination(BI first, BI mid, BI last) {
  return next_combination_imp(first, mid, mid, last);
}

int main(void) {
  int a[5];
  REP(i, 0, 5) a[i] = i;
  do {
    REP(i, 0, 3) cout << a[i] << " ";
    cout << endl;
  } while(next_combination(a, a + 3, a + 5));

  return 0;
}
