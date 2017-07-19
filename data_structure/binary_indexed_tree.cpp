#include <iostream>
#include <vector>
#define REP(i, a, n) for(int i = ((int) a); i < ((int) n); i++)
using namespace std;

/* 0-indexed */
class BinaryIndexedTree {
  vector<int> v;

public:
  BinaryIndexedTree(int n) {
    REP(i, 0, n) v.push_back(0);
  }

  int query(int i) {
    if(!(i + 1)) return 0;
    return binop(v[i], query((i + 1) - ((i + 1) & -(i + 1)) - 1));
  }

  void update(int i, int n) {
    if(i > v.size()) return;
    v[i] = binop(v[i], n);
    update((i + 1) + ((i + 1) & -(i + 1)) - 1, n);
  }

private:
  int binop(int a, int b) {
    return a + b;
  }
};

int main(void) {
  BinaryIndexedTree bit(5);      // [0, 0, 0, 0, 0]
  bit.update(2, 2);              // [0, 0, 2, 0, 0]
  cout << bit.query(1) << endl;  // 0
  cout << bit.query(2) << endl;  // 2
  bit.update(3, 5);              // [0, 0, 2, 5, 0]
  cout << bit.query(3) << endl;  // 7
  bit.update(0, 8);              // [8, 0, 2, 5, 0]
  cout << bit.query(2) << endl;  // 10
  cout << bit.query(4) << endl;  // 15

  return 0;
}
