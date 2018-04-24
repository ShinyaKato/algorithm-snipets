#include "header.h"
#include "src.cpp"

int main(void) {
  UnionFind uf(5);
  uf.unite(1, 2);
  uf.unite(0, 4);

  vector<ll> expect = { 0, 1, 1, 3, 0 };
  REP(i, 0, 5) assert(uf.find(i) == expect[i]);
}
