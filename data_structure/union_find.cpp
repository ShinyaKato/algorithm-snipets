#include <iostream>
#include <vector>
#define REP(i, a, n) for(int i = ((int) a); i < ((int) n); i++)
using namespace std;

class UnionFind {
  vector<int> a;

public:
  UnionFind(int n) {
    REP(i, 0, n) a.push_back(i);
  }

  int find(int i) {
    return a[i] == i ? i : (a[i] = find(a[i]));
  }

  bool unite(int i, int j) {
    if(find(i) == find(j)) return false;
    a[find(i)] = find(j);
    return true;
  }

  bool root(int i) {
    return i == find(i);
  }

  bool same(int i, int j) {
    return find(i) == find(j);
  }
};

int main(void) {
  UnionFind u(5);
  u.unite(1, 2);
  u.unite(0, 4);
  REP(i, 0, 5) cout << u.find(i) << endl;

  return 0;
}
