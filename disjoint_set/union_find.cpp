#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

/* UnionFind: 素集合データ構造に対して以下の2つの操作を行うアルゴリズム
 *   find:  要素がどの集合に属しているかを求める
 *   unite: 2つの集合を1つに統合する
 *
 * 初期状態ではdataは全て-1で初期化される
 * dataの値が負である場合はその要素が集合の代表点であることを表し、絶対値はその集合の要素数を表す
 * 値が非負整数の場合、その要素の親要素を表す
 *
 * constructor(n): 要素数nで初期化する
 * find(i):        要素iが属する集合を返す
 * unite(i, j):    要素i, jが属する集合を統合する(iをjの親にする), もともと同じ集合ならばfalseを返す
 * size(i):        要素iが属する集合のサイズを返す
 * root(i):        要素iが集合の代表点(木の根)になっているかを返す
 * same(i, j):     要素i, jが同じ集合に属すかを返す
 *
 */

class UnionFind {
private:
  vector<ll> data;

public:
  UnionFind(ll n): data(n, -1) {}

  ll size(ll i) { return -data[find(i)]; }
  bool root(ll i) { return data[i] < 0; }
  bool same(ll i, ll j) { return find(i) == find(j); }

  ll find(ll i) { return root(i) ? i : (data[i] = find(data[i])); }

  bool unite(ll i, ll j) {
    if(same(i, j)) return false;
    data[find(i)] += data[find(j)];
    data[find(j)] = find(i);
    return true;
  }
};

int main(void) {
  UnionFind uf(5);
  uf.unite(1, 2);
  uf.unite(0, 4);

  vector<ll> expect = { 0, 1, 1, 3, 0 };
  REP(i, 0, 5) assert(uf.find(i) == expect[i]);
}
