/* index
 *
 * data_structure
 *   binary_indexed_tree.cpp
 *   binary_indexed_tree_2d.cpp
 *   segment_tree/src.cpp
 *   lazy_segment_tree.cpp
 *   starry_sky_tree.cpp
 *   convex_hull_trick.cpp
 *
 * disjoint_set
 *   union_find.cpp
 *
 * dynamic_programming
 *   least_increasing_subsequence_pair.cpp
 *   monotone_minima.cpp
 *
 * geometory
 *   geometry.cpp
 *   3d.cpp
 *   point_to_line_segment_distance_3d.cpp
 *
 * graph
 *   bellmanford.cpp
 *   dijkstra.cpp
 *   max_flow.cpp
 *   min_cost_flow.cpp
 *   lowest_common_ancestor.cpp
 *   strongly_connected_component.cpp
 *   centroid.cpp
 *   centroid_decomposition.cpp
 *
 * integer
 *   modulo_inverse.cpp
 *   modulo_power.cpp
 *   modulo_combination.cpp
 *   combination.cpp
 *   matrix_poewr.cpp
 *   modint.cpp
 *   rational.cpp
 *   modratio.cpp
 *   next_combination.cpp
 *   next_pertial_permutation.cpp
 *
 * math
 *   dice.cpp
 *
 * matrix
 *   hungarian.cpp
 *
 * string
 *   split.cpp
 *   suffix_array.cpp
 *   aho_corasick.cpp
 *   rolling_hash.cpp
 *
 */

/******************************************/
/* data_structure/binary_indexed_tree.cpp */
/******************************************/

/* 1-indexed, [1, n] */
template<typename T> class BinaryIndexedTree {
  vector<T> vec;
  const ll n;

public:
  BinaryIndexedTree(T _n) : vec(_n + 1), n(_n) {}

  T query(ll x) { /* query for [1, x] */
    T ret = 0;
    for(ll i = x; i > 0; i -= i & (-i)) ret += vec[i];
    return ret;
  }

  void update(ll x, T k) { /* update for [1, x] */
    for(ll i = x; i <= n; i += i & (-i)) vec[i] += k;
  }
};

/*********************************************/
/* data_structure/binary_indexed_tree_2d.cpp */
/*********************************************/

/* 1-indexed, [(1, 1), (m, n)] */
template<typename T> class BinaryIndexedTree2D {
  vector< vector<T> > vec;
  const ll m, n;

public:
  BinaryIndexedTree2D(ll _m, ll _n) : vec(_m + 1, vector<T>(_n + 1)), m(_m), n(_n) {}

  T query(ll y, ll x) { /* query for [(1, 1), (y, x)] */
    T ret = 0;
    for(ll i = y; i > 0; i -= i & (-i))
      for(ll j = x; j > 0; j -= j & (-j))
        ret += vec[i][j];
    return ret;
  }

  void update(ll y, ll x, T k) { /* update for [(1, 1,), (y, x)] */
    for(ll i = y; i <= m; i += i & (-i))
      for(ll j = x; j <= n; j += j & (-j))
        vec[i][j] += k;
  }
};

/***************************************/
/* data_structure/segment_tree/src.cpp */
/***************************************/

/* 0-indexed, [0, n)
 *
 * requirements: let a, b, c in T
 *   op(op(a, b), c) = op(a, op(b, c))
 *   op(a, e) = op(e, a) = e
 */
template<typename T, typename E> class SegmentTree {
public:
  typedef function<T (T, T)> Operator;
  typedef function<T (T, E)> Apply;

  vector<T> data;
  ll n;        // size of elements (2^x alignment)
  T e;         // identity of monoid
  Operator op; // binary operator of monoid
  Apply apply; // apply effect to monoid

  // construct with size of elements
  SegmentTree(ll _n, T e, Operator op, Apply apply): e(e), op(op), apply(apply) {
    for(n = 1; n < _n; n *= 2);
    data.resize(n * 2 - 1, e);
  }

  // construct with initial values
  SegmentTree(const vector<T> &vec, T e, Operator op, Apply apply): e(e), op(op), apply(apply) {
    for(n = 1; n < vec.size(); n *= 2);
    data.resize(n * 2 - 1, e);
    REP(i, 0, vec.size()) data[i + n - 1] = vec[i];
    for(ll i = n - 2; i >= 0; i--) data[i] = op(data[i * 2 + 1], data[i * 2 + 2]);
  }

  // query for [a, b)
  T query(ll a, ll b) { return query(a, b, 0, 0, n); }
  T query(ll a, ll b, ll k, ll l, ll r) {
    if(r <= a || b <= l) return e;
    if(a <= l && r <= b) return data[k];
    T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    return op(vl, vr);
  }

  // update value at k
  void update(ll k, E x) {
    k += n - 1;
    data[k] = apply(data[k], x);
    while(k > 0) {
      k = (k - 1) / 2;
      data[k] = op(data[k * 2 + 1], data[k * 2 + 2]);
    }
  }
};

/****************************************/
/* data_structure/lazy_segment_tree.cpp */
/****************************************/

/* 0-indexed, [0, n)
 *
 * requirements:
 * let a, b, c in T, x, y, z in E
 *   op(op(a, b), c) = op(a, op(b, c))
 *   op(a, e) = op(e, a) = e
 *   merge(merge(x, y), z) = merge(x, merge(y, z))
 *   merge(x, d) = merge(d, x) = d
 *   apply(apply(a, x), y) = apply(a, merge(x, y))
 *   apply(a, d) = a
 */
template<typename T, typename E> class LazySegmentTree {
public:
  typedef function<T (T, T)> Operator;
  typedef function<E (E, E)> Merge;
  typedef function<T (T, E)> Apply;
  typedef function<E (E, ll)> Product;

  vector<T> data;
  vector<E> lazy;
  ll n;        // size of elements (2^x alignment)
  T e;         // identity of monoid
  Operator op; // binary operator of monoid
  E d;         // identity of effect
  Merge merge; // merge effects
  Apply apply; // apply effect to monoid
  Product p;   // calculate effect * n

  // construction with size of elements
  LazySegmentTree(ll _n, T e, Operator op, E d, Merge merge, Apply apply, Product p):
    e(e), op(op), d(d), merge(merge), apply(apply), p(p) {
    for(n = 1; n < _n; n *= 2);
    data.resize(n * 2 - 1, e);
    lazy.resize(n * 2 - 1, d);
  }

  // construction with initial values
  LazySegmentTree(const vector<T> &vec, T e, Operator op, E d, Merge merge, Apply apply, Product p):
    e(e), op(op), d(d), merge(merge), apply(apply), p(p) {
    for(n = 1; n < (ll) vec.size(); n *= 2);
    data.resize(n * 2 - 1, e);
    lazy.resize(n * 2 - 1, d);
    REP(i, 0, vec.size()) data[i + n - 1] = vec[i];
    for(ll i = n - 2; i >= 0; i--) data[i] = op(data[i * 2 + 1], data[i * 2 + 2]);
  }

  // evaluate lazy update
  void eval(ll k, ll l, ll r) {
    if(r - l > 1) {
      lazy[k * 2 + 1] = merge(lazy[k * 2 + 1], lazy[k]);
      lazy[k * 2 + 2] = merge(lazy[k * 2 + 2], lazy[k]);
    }
    data[k] = apply(data[k], p(lazy[k], r - l));
    lazy[k] = d;
  }

  // query for [a, b)
  T query(ll a, ll b) { return query(a, b, 0, 0, n); }
  T query(ll a, ll b, ll k, ll l, ll r) {
    eval(k, l, r);
    if(r <= a || b <= l) return e;
    if(a <= l && r <= b) return data[k];
    T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
    T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
    return op(vl, vr);
  }

  // update values of [a, b)
  T update(ll a, ll b, E x) { return update(a, b, x, 0, 0, n); }
  T update(ll a, ll b, E x, ll k, ll l, ll r) {
    eval(k, l, r);
    if(r <= a || b <= l) return data[k];
    if(a <= l && r <= b) {
      lazy[k] = merge(lazy[k], x);
      return apply(data[k], p(lazy[k], r - l));
    }
    T vl = update(a, b, x, k * 2 + 1, l, (l + r) / 2);
    T vr = update(a, b, x, k * 2 + 2, (l + r) / 2, r);
    return data[k] = op(vl, vr);
  }
};

/**************************************/
/* data_structure/starry_sky_tree.cpp */
/**************************************/

#define LOWER_BOUND(a, v) lower_bound(a.begin(), a.end(), v) - a.begin()
#define UPPER_BOUND(a, v) upper_bound(a.begin(), a.end(), v) - a.begin()

class StarrySkyTree {
  vector<ll> all, dat;
  ll n;

public:
  StarrySkyTree(ll _n) : n(1) {
    while(n < _n) n *= 2;
    all.resize(n * 2 - 1, 0);
    dat.resize(n * 2 - 1, 0);
  }

  ll minimum(ll a, ll b) { return minimum(a, b, 0, 0, n); }
  ll minimum(ll a, ll b, ll k, ll l, ll r) {
    if(r <= a || b <= l) return 0;
    if(a <= l && r <= b) return all[k] + dat[k];
    ll vl = minimum(a, b, k * 2 + 1, l, (l + r) / 2);
    ll vr = minimum(a, b, k * 2 + 2, (l + r) / 2, r);
    return min(vl, vr) + all[k];
  }

  void add(ll a, ll b, ll x) { add(a, b, x, 0, 0, n); }
  void add(ll a, ll b, ll x, ll k, ll l, ll r) {
    if(a <= l && r <= b) all[k] += x;
    else if(l < b && a < r) {
      add(a, b, x, k * 2 + 1, l, (l + r) / 2);
      add(a, b, x, k * 2 + 2, (l + r) / 2, r);
      dat[k] = min(all[k * 2 + 1] + dat[k * 2 + 1], all[k * 2 + 2] + dat[k * 2 + 2]);
    }
  }
};

/****************************************/
/* data_structure/convex_hull_trick.cpp */
/****************************************/

class ConvexHullTrick {
  vector<pll> deq;
  ll s, t;

public:
  ConvexHullTrick(ll n) { /* n: number of lines */
    deq.resize(n);
    s = 0, t = 0;
  }

  void add(ll a, ll b) { /* a must decrease monotonously */
    const pll p(a, b);
    while(s + 1 < t && check(deq[t - 2], deq[t - 1], p)) t--;
    deq[t++] = p;
  }

  ll query(ll x) { /* O(log n) */
    ll low = s - 1, high = t - 1;
    while(low + 1 < high) {
      ll mid = (low + high) / 2;
      if(isright(deq[mid], deq[mid + 1], x)) low = mid;
      else high = mid;
    }
    return f(deq[high], x);
  }

private:
  bool isright(const pll &p1, const pll &p2, ll x) {
    return (p1.second - p2.second) >= x * (p2.first - p1.first);
  }

  bool check(const pll &p1, const pll &p2, const pll &p3) {
    return (p2.first - p1.first) * (p3.second - p2.second) >= (p2.second - p1.second) * (p3.first - p2.first);
  }

  ll f(const pll &p, ll x) {
    return p.first * x + p.second;
  }
};

/***********************************/
/* disjoint_set/union_find.cpp */
/***********************************/

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

/*************************************************************/
/* dynamic_programming/least_increasing_subsequence_pair.cpp */
/*************************************************************/

ll lis_rect(vector<pll> &rect) {
  ll N = rect.size();
  sort(rect.begin(), rect.end());

  ll dp[N];
  REP(i, 0, N) dp[i] = INF;
  REP(i, 0, N) *lower_bound(dp, dp + N, rect[i].second) = rect[i].second;

  return lower_bound(dp, dp + N, INF) - dp;
}

/*******************************************/
/* dynamic_programming/monotone_minima.cpp */
/*******************************************/

/* il, ir, jl, jr: [il, ir), [jl, jr)
 * f(i, j):
 *   arg(i) := f(i, j)のあるiを決めた時にf(i, _)に最小を与えるj
 *   j1 = arg(i1), j2 = arg(i2), i1 < i2ならばj1 <= j2
 */
void dfs(ll il, ll ir, ll jl, ll jr, function<ll(ll, ll)> &f, vector<ll> &ans) {
  if(il >= ir) return;

  ll im = (il + ir) / 2, jm;
  ans[im] = INF;
  REP(j, jl, jr) {
    ll v = f(im, j);
    if(ans[im] > v) {
      ans[im] = v;
      jm = j;
    }
  }

  dfs(il, im, jl, jm + 1, f, ans);
  dfs(im + 1, ir, jm, jr, f, ans);
}

/**************************/
/* geometory/geometry.cpp */
/**************************/

class Vector2 {
public:
  double x, y;

  Vector2(): x(0), y(0) {}
  Vector2(double x, double y): x(x), y(y) {}

  Vector2 operator+(Vector2 p) { return Vector2(x + p.x, y + p.y); }
  Vector2 operator-(Vector2 p) { return Vector2(x - p.x, y - p.y); }

  Vector2 operator*(double t) { return Vector2(x * t, y * t); }
  Vector2 operator/(double t) { return Vector2(x / t, y / t); }

  double dot(Vector2 p) { return x * p.x + y * p.y; }
  double det(Vector2 p) { return x * p.y - y * p.x; }

  double norm2() { return x * x + y * y; }
  double norm() { return sqrt(norm2()); }

  Vector2 normalize() { return Vector2(x / norm(), y / norm()); }

  friend ostream& operator<<(ostream &out, const Vector2 &v) {
    out << "(" << v.x << ", " << v.y << ")";
  }
};
using Point2 = Vector2;

class LineSegment2 {
public:
  Point2 l1, l2;

  LineSegment2() {}
  LineSegment2(Point2 l1, Point2 l2): l1(l1), l2(l2) {}

  friend ostream& operator<<(ostream& out, const LineSegment2& s) {
    out << "(" << s.l1 << ", " << s.l2 << ")";
  }
};

/* 点Pと点L1, L2を通る直線の距離 */
double point_to_line_distance(Point2 p, Point2 l1, Point2 l2) {
  Vector2 d = l2 - l1;                       // L1からL2への方向のベクトル
  Vector2 v = p - l1;                        // L1からPへの方向のベクトル
  return sqrt(pow(d.det(v), 2) / d.norm2()); // 垂線の足から直線への距離
}

/* 点Pと点L1, L2を端点とする線分の距離 */
double point_to_line_segment_distance(Point2 p, Point2 l1, Point2 l2) {
  Vector2 d = l2 - l1;                       // L1からL2への方向のベクトル
  Vector2 v = p - l1;                        // L1からPへの方向のベクトル
  double t = d.dot(v) / d.norm2();           // Pから線分に垂線を下ろした足とL0の距離の割合
  if(t < 0) return (l1 - p).norm();          // 垂線の足からL1の方が近い場合
  if(t > 1) return (l2 - p).norm();          // 垂線の足からL2の方が近い場合
  return sqrt(pow(d.det(v), 2) / d.norm2()); // 垂線の足から直線への距離
}

/* 点A, Bを端点とする線分と点C, Dを端点とする線分の交差判定 */
bool line_segments_intersect(Point2 a, Point2 b, Point2 c, Point2 d) {
  double ta = (a - c).det(d - c);     // 点Aが直線CDに対して上側にあるか下側にあるか
  double tb = (b - c).det(d - c);     // 点Bが直線CDに対して上側にあるか下側にあるか
  double tc = (c - a).det(b - a);     // 点Cが直線ABに対して上側にあるか下側にあるか
  double td = (d - a).det(b - a);     // 点Dが直線ABに対して上側にあるか下側にあるか
  return ta * tb < 0 && tc * td < 0;  // 点Aと点Bが逆側にありかつ点Cと点Dが逆側にあれば交差している
}

/* 点A, Bを通る直線と点C, Dを通る直線の交点 */
Point2 lines_intersect_point(Point2 a, Point2 b, Point2 c, Point2 d) {
  Vector2 u = b - a;                          // u: AからB方向へのベクトル
  Vector2 v = d - c;                          // v: CからD方向へのベクトル
  double p1 = u.y, q1 = -u.x, r1 = -u.det(a); // p1 * x + a1 * y = r1
  double p2 = v.y, q2 = -v.x, r2 = -v.det(c); // p2 * x + a2 * y = r2
  double det = p1 * q2 - p2 * q1;             // 行列の行列式
  double x = (r1 * q2 - r2 * q1) / det;       // x座標(逆行列をかける)
  double y = (r2 * p1 - r1 * p2) / det;       // y座標(逆行列をかける)
  return Point2(x, y);
}

/* convex hull */
vector<Point2> convex_hull(vector<Point2> ps) {
  sort(ps.begin(), ps.end(), [](const Point2 &p, const Point2 &q) {
    if(p.x != q.x) return p.x < q.x;
    return p.y < q.y;
  });

  ll n = ps.size(), k = 0;
  vector<Point2> qs(n * 2);
  REP(i, 0, n) {
    while(k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  for(ll i = n - 2, t = k; i >= 0; i--) {
    while(k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  qs.resize(k - 1);

  /* counter clockwise, first vertix is lexicographically smallest */
  return qs;
}

/********************/
/* geometory/3d.cpp */
/********************/

class Vector3 {
public:
  double x, y, z;

  Vector3(): x(0), y(0), z(0) {}
  Vector3(double x, double y, double z): x(x), y(y), z(z) {}

  Vector3 operator+(Vector3 p) { return Vector3(x + p.x, y + p.y, z + p.z); }
  Vector3 operator-(Vector3 p) { return Vector3(x - p.x, y - p.y, z - p.z); }

  Vector3 operator*(double t) { return Vector3(x * t, y * t, z * t); }
  Vector3 operator/(double t) { return Vector3(x / t, y / t, z / t); }

  double dot(Vector3 p) { return x * p.x + y * p.y + z * p.z; }
  Vector3 det(Vector3 p) { return Vector3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }

  double norm2() { return x * x + y * y + z * z; }
  double norm() { return sqrt(norm2()); }

  Vector3 normalize() { return Vector3(x / norm(), y / norm(), z / norm()); }

  friend ostream& operator<<(ostream &out, const Vector3 &v) {
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  }
};

class Quaternion {
public:
  Vector3 v;
  double w;

  Quaternion(): v(0, 0, 0), w(0) {}
  Quaternion(Vector3 v): v(v), w(0) {}
  Quaternion(Vector3 v, double w): v(v), w(w) {}
  Quaternion(double x, double y, double z, double w): v(x, y, z), w(w) {}

  Quaternion operator+(Quaternion q) { return Quaternion(v + q.v, w + q.w); }
  Quaternion operator-(Quaternion q) { return Quaternion(v - q.v, w - q.w); }

  Quaternion operator*(double t) { return Quaternion(v * t, w * t); }
  Quaternion operator/(double t) { return Quaternion(v / t, w / t); }

  Quaternion operator*(Quaternion q) { return Quaternion(v.det(q.v) + q.v * w + v * q.w, w * q.w - v.dot(q.v)); }

  double norm2() { return v.norm2() + w * w; }
  double norm() { return sqrt(norm2()); }

  Quaternion conjugation() { return Quaternion(v * -1, w); }
  Quaternion inverse() { return conjugation() / norm2(); }

  friend ostream& operator<<(ostream &out, const Quaternion &q) {
    out << "(" << q.v << ", " << q.w << ")";
  }
};

Vector3 rotate(Vector3 v, Vector3 u, double theta) {
  Quaternion q1(u * sin(theta / 2), cos(theta / 2));
  Quaternion q2 = q1.inverse();
  Quaternion p(v);
  Quaternion t = q1 * p * q2;

  return t.v;
}

/***************************************************/
/* geometory/point_to_line_segment_distance_3d.cpp */
/***************************************************/

struct Point3D { double x, y, z; };
struct Line3D { Point3D p, q; };

double distance(Line3D l, Point3D p) {
  double x0 = p.x, y0 = p.y, z0 = p.z;
  double x1 = l.p.x, y1 = l.p.y, z1 = l.p.z;
  double x2 = l.q.x, y2 = l.q.y, z2 = l.q.z;
  double a = x2 - x1;
  double b = y2 - y1;
  double c = z2 - z1;
  double a2 = a * a;
  double b2 = b * b;
  double c2 = c * c;
  double r2 = a2 + b2 + c2;
  double t2 = -(a * (x1 - x0) + b * (y1 - y0) + c * (z1 - z0));
  if(t2 < 0) return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0) * (z1 - z0));
  if(t2 > r2) return sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0) + (z2 - z0) * (z2 - z0));
  double fx = b * (z1 - z0) - c * (y1 - y0);
  double fy = c * (x1 - x0) - a * (z1 - z0);
  double fz = a * (y1 - y0) - b * (x1 - x0);
  double f2 = fx * fx + fy * fy + fz * fz;
  return sqrt(f2 / r2);
}

/*************************/
/* graph/bellmanford.cpp */
/*************************/

struct edge { ll v, d; };

/* initialization of d
 *   1. find shortest path from s: d[i] = INF, d[s] = 0
 *   2. find negative loop:        d[i] = 0
 */
bool bellmanford(vector< vector<edge> > &E, vector<ll> &d) {
  bool updated;
  REP(k, 0, E.size()) {
    updated = false;
    REP(u, 0, E.size()) for(edge e : E[u]) if(d[e.v] > d[u] + e.d) {
      d[e.v] = d[u] + e.d;
      updated = true;
    }
  }
  return updated;
}

/* shortest path from s */
vector<ll> shortest_path(vector< vector< edge> > &E, ll s) {
  vector<ll> d(E.size(), INF);
  d[s] = 0;
  bellmanford(E, d);
  return d;
}

/* negative loop */
bool find_negative_loop(vector< vector<edge> > &E) {
  vector<ll> d(E.size(), 0);
  return bellmanford(E, d);
}

/**********************/
/* graph/dijkstra.cpp */
/**********************/

class Dijkstra {
public:
  struct edge { ll v, dist; };

  struct state {
    ll v, cost;
    bool operator>(const state s) const { return cost > s.cost; }
  };

  const ll INF = (1LL << 60);
  ll N;
  vector< vector<edge> > E;

  Dijkstra(ll n): N(n), E(n) {}

  void add_directed_edge(ll u, ll v, ll d) {
    E[u].push_back((edge) { v, d });
  }

  void add_undirected_edge(ll u, ll v, ll d) {
    E[u].push_back((edge) { v, d });
    E[v].push_back((edge) { u, d });
  }

  vector<ll> shortest_path(ll S) {
    vector<ll> dp(E.size(), INF);
    priority_queue<state, vector<state>, greater<state> > q;
    q.push((state) { S, 0 });
    while(!q.empty()) {
      ll v = q.top().v, cost = q.top().cost;
      q.pop();
      if(dp[v] <= cost) continue;
      dp[v] = cost;
      REP(i, 0, E[v].size()) {
        ll nv = E[v][i].v, ncost = cost + E[v][i].dist;
        if(dp[nv] > ncost) q.push((state) { nv, ncost });
      }
    }
    return dp;
  }
};

/**********************/
/* graph/max_flow.cpp */
/**********************/

class MaxFlow {
public:
  struct edge { ll to, cap, rev; };

  const ll INF = 1LL << 60;
  ll N;
  vector< vector<edge> > E;
  vector<bool> used;

  MaxFlow(ll n): N(n), E(n), used(n) {};

  void add_directed_edge(ll from, ll to, ll cap) {
    E[from].push_back((edge) { to, cap, (ll) E[to].size() });
    E[to].push_back((edge) { from, 0, (ll) E[from].size() - 1 });
  }

  void add_undirected_edge(ll from, ll to, ll cap) {
    E[from].push_back((edge) { to, cap, (ll) E[to].size() });
    E[to].push_back((edge) { from, cap, (ll) E[from].size() - 1 });
  }

  ll dfs(ll v, ll t, ll f) {
    if(v == t) return f;
    used[v] = true;
    REP(i, 0, E[v].size()) {
      edge &e = E[v][i];
      if(!used[e.to] && e.cap > 0) {
        ll d = dfs(e.to, t, min(f, e.cap));
        if(d > 0) {
          e.cap -= d;
          E[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  ll max_flow(ll s, ll t) {
    ll flow = 0;
    while(1) {
      REP(i, 0, N) used[i] = false;
      ll f = dfs(s, t, INF);
      if(f == 0 || f == INF) break;
      flow += f;
    }
    return flow;
  }
};

/***************************/
/* graph/min_cost_flow.cpp */
/***************************/

class MinCostFlow {
public:
  struct edge { ll to, cap, cost, rev; };

private:
  ll V;
  vector< vector<edge> > G;
  vector<ll> h, dist, prevv, preve;

public:
  MinCostFlow(ll V): V(V), G(V), h(V, 0), dist(V), prevv(V), preve(V) {}

  void add_edge(ll from, ll to, ll cap, ll cost) {
    G[from].push_back((edge) { to, cap, cost, (ll) G[to].size() });
    G[to].push_back((edge) { from, 0, -cost, (ll) G[from].size() - 1 });
  }

  ll min_cost_flow(ll s, ll t, ll f) {
    ll ret = 0;
    while(f > 0) {
      priority_queue<pll, vector<pll>, greater<pll> > q;
      REP(i, 0, V) dist[i] = INF;
      dist[s] = 0;
      q.push(pll(0, s));
      while(!q.empty()) {
        pll p = q.top();
        q.pop();
        ll v = p.second;
        if(dist[v] < p.first) continue;
        REP(i, 0, G[v].size()) {
          edge &e = G[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            q.push(pll(dist[e.to], e.to));
          }
        }
      }
      if(dist[t] == INF) return -1;
      REP(v, 0, V) h[v] += dist[v];
      ll d = f;
      for(ll v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
      f -= d;
      ret += d * h[t];
      for(ll v = t; v != s; v = prevv[v]) {
        edge &e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return ret;
  }
};

/************************************/
/* graph/lowest_common_ancestor.cpp */
/************************************/

class LowestCommonAncestor {
public:
  ll vmax, lmax, *depth, **parent;
  vector<ll> *edge;

  LowestCommonAncestor(ll vmax): vmax(vmax) {
    ll p = 1;
    for(lmax = 1; p < vmax; lmax++) p *= 2;
    edge = new vector<ll>[vmax];
    depth = new ll[vmax];
    parent = new ll*[lmax];
    REP(i, 0, lmax) parent[i] = new ll[vmax];
  }

  void init(ll root) {
    dfs(root, -1, 0);
    REP(i, 0, lmax - 1) REP(j, 0, vmax) {
      parent[i + 1][j] = parent[i][j] >= 0 ? parent[i][parent[i][j]] : -1;
    }
  }

  ll query(ll u, ll v) {
    if(depth[u] > depth[v]) swap(u, v);
    REP(i, 0, lmax) if(((depth[v] - depth[u]) >> i) & 1) v = parent[i][v];
    if(u == v) return u;
    for(ll i = lmax - 1; i >= 0; i--) if(parent[i][u] != parent[i][v]) {
      u = parent[i][u];
      v = parent[i][v];
    }
    return parent[0][u];
  }

private:
  void dfs(ll v, ll p, ll d) {
    parent[0][v] = p;
    depth[v] = d;
    REP(i, 0, edge[v].size()) if(edge[v][i] != p) dfs(edge[v][i], v, d + 1);
  }
};

/******************************************/
/* graph/strongly_connected_component.cpp */
/******************************************/

class StronglyConnectedComponent {
public:
  const ll N;
  vector< vector<ll> > E, R;
  vector<ll> component;

  StronglyConnectedComponent(ll N): N(N), E(N), R(N), component(N) {}

  void add_edge(ll u, ll v) {
    E[u].push_back(v);
    R[v].push_back(u);
  }

  ll discomposit() {
    vector<ll> vs;
    vector<bool> used1(N, false);
    REP(i, 0, N) if(!used1[i]) dfs(i, vs, used1);

    vector<bool> used2(N, false);
    ll k = 0;
    for(ll i = vs.size() - 1; i >= 0; i--) if(!used2[vs[i]]) rdfs(vs[i], k++, used2);
    return k;
  }

private:
  void dfs(ll v, vector<ll> &vs, vector<bool> &used) {
    used[v] = true;
    REP(i, 0, E[v].size()) if(!used[E[v][i]]) dfs(E[v][i], vs, used);
    vs.push_back(v);
  }

  void rdfs(ll v, ll k, vector<bool> &used) {
    used[v] = true;
    component[v] = k;
    REP(i, 0, R[v].size()) if(!used[R[v][i]]) rdfs(R[v][i], k, used);
  }
};

/**********************/
/* graph/centroid.cpp */
/**********************/

vector<ll> centroid(vector< vector<ll> > &E) {
  ll N = E.size();
  vector<ll> cnt(N);
  vector<ll> c;
  function<void (ll, ll)> dfs = [&](ll v, ll p) {
    bool ok = true;
    cnt[v] = 1;
    for(ll u : E[v]) if(u != p) {
      dfs(u, v);
      ok = ok && (cnt[u] <= N / 2);
      cnt[v] += cnt[u];
    }
    ok = ok && (N - cnt[v] <= N / 2);
    if(ok) c.push_back(v);
  };
  dfs(0, -1);
  return c;
}

vector<ll> centroid_with_dead(vector< vector<ll> > &E, ll v, vector<bool> &dead) {
  function<ll (ll, ll)> subtree_size = [&](ll v, ll p) {
    ll sum = 1;
    for(ll u : E[v]) if(u != p && !dead[u]) sum += subtree_size(u, v);
    return sum;
  };
  ll N = subtree_size(v, -1);
  vector<ll> cnt(E.size());
  vector<ll> c;
  function<void (ll, ll)> dfs = [&](ll v, ll p) {
    bool ok = true;
    cnt[v] = 1;
    for(ll u : E[v]) if(u != p && !dead[u]) {
      dfs(u, v);
      ok = ok && (cnt[u] <= N / 2);
      cnt[v] += cnt[u];
    }
    ok = ok && (N - cnt[v] <= N / 2);
    if(ok) c.push_back(v);
  };
  dfs(v, -1);
  return c;
}

/************************************/
/* graph/centroid_decomposition.cpp */
/************************************/

struct edge {
  ll to;
  /* add other attributes of a edge. */
};
typedef vector< vector<edge> > graph;

ll tree_size(ll v, ll p, graph &E, vector<bool> &dead) {
  ll sum = 1;
  for(edge e : E[v]) if(e.to != p && !dead[e.to]) sum += tree_size(e.to, v, E, dead);
  return sum;
};

pll centroid(ll v, ll p, ll n, graph &E, vector<bool> &dead) {
  bool ok = true;
  ll cnt = 1;
  for(edge e : E[v]) if(e.to != p && !dead[e.to]) {
    pll r = centroid(e.to, v, n, E, dead);
    if(r.first >= 0) return r;
    ok = ok && (r.second <= n / 2);
    cnt += r.second;
  }
  ok = ok && (n - cnt <= n / 2);
  return pll(ok ? v : -1, cnt);
};

/* template of centroid decomposition */
void subtree(ll v, graph &E, vector<bool> &dead) {
  ll n = tree_size(v, -1, E, dead);
  ll c = centroid(v, -1, n, E, dead).first;
  dead[c] = true;

  for(edge e : E[c]) if(!dead[e.to]) subtree(e.to, E, dead);

  /* compute something about whole of the tree. */
  /* compute something using result of subtrees decomposited by centroid. */

  dead[c] = false;
}

/******************************/
/* integer/modulo_inverse.cpp */
/******************************/

ll modulo_inverse(ll n) {
  ll t = MOD - 2, p = 1, q = n;
  while(t > 0) {
    if(t % 2) p = (p * q) % MOD;
    q = (q * q) % MOD;
    t /= 2;
  }
  return p % MOD;
}

/****************************/
/* integer/modulo_power.cpp */
/****************************/

ll modulo_power(ll a, ll n) {
  if(n == 0) return 1;
  if(n % 2 == 0) return modulo_power((a * a) % MOD, n / 2);
  return (a * modulo_power(a, n - 1)) % MOD;
}

/***************************/
/* integer/combination.cpp */
/***************************/

ll combination(int n, int r) {
  static ll comb[51][51];
  ll &ret = comb[n][r];
  if(ret != 0) return ret;
  if(n == 0 || r == 0) return ret = 1;
  if(n == r) return ret = 1;
  if(r == 1) return ret = n;
  return ret = combination(n - 1, r - 1) + combination(n - 1, r);
}

/**********************************/
/* integer/modulo_combination.cpp */
/**********************************/

class ModuloCombination {
private:
  vector<ll> fact, fact_inv;

  static ll mod_pow(ll a, ll n) {
    if(n == 0) return 1;
    if(n % 2 == 0) return mod_pow((a * a) % MOD, n / 2);
    return (a * mod_pow(a, n - 1)) % MOD;
  }

public:
  ModuloCombination(ll N): fact(N + 1), fact_inv(N + 1) {
    fact[0] = 1;
    REP(i, 1, N + 1) fact[i] = (i * fact[i - 1]) % MOD;
    REP(i, 0, N + 1) fact_inv[i] = mod_pow(fact[i], MOD - 2);
  }

  ll operator()(ll n, ll r) {
    return fact[n] * fact_inv[r] % MOD * fact_inv[n - r] % MOD;
  }
};

/****************************/
/* integer/matrix_poewr.cpp */
/****************************/

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

/**********************/
/* integer/modint.cpp */
/**********************/

class modint {
  ll n;

public:
  modint(): n(0) {};
  modint(ll _n): n((_n + MOD) % MOD) {}
  modint(const modint &i): n(i.n) {}
  operator ll() const { return n; }

  modint operator+(const modint &i) const { return modint(n + i.n); }
  modint operator-(const modint &i) const { return modint(n - i.n); }
  modint operator*(const modint &i) const { return modint(n * i.n); }
  modint operator/(const modint &i) const { return modint(n * i.inverse().n); }

  modint operator+=(const modint &i) { return *this = *this + i; }
  modint operator-=(const modint &i) { return *this = *this - i; }
  modint operator*=(const modint &i) { return *this = *this * i; }
  modint operator/=(const modint &i) { return *this = *this / i; }

  modint inverse() const {
    modint p = 1, q = n;
    for(ll t = MOD - 2; t > 0; t /= 2) {
      if(t % 2) p *= q;
      q *= q;
    }
    return p;
  }
};

/************************/
/* integer/rational.cpp */
/************************/

class rational {
  ll n, d;

  static ll gcd(ll a, ll b) { return b != 0 ? gcd(b, a % b) : a; }

public:
  rational(): n(0), d(1) {}
  rational(ll _n): n(_n), d(1) {}
  rational(ll _n, ll _d) {
    assert(_d != 0);
    ll g = gcd(abs(_n), abs(_d));
    n = _n / g * (_d / abs(_d));
    d = abs(_d) / g;
  }

  bool operator==(rational r) const { return n * r.d == d * r.n; }
  bool operator!=(rational r) const { return !(*this == r); }
  bool operator<(rational r) const { return n * r.d < d * r.n; }
  bool operator>(rational r) const { return n * r.d > d * r.n; }
  bool operator<=(rational r) const { return *this == r || *this < r; }
  bool operator>=(rational r) const { return *this == r || *this > r; }

  rational operator+(rational r) const { return rational(n * r.d + d * r.n, d * r.d); }
  rational operator-(rational r) const { return rational(n * r.d - d * r.n, d * r.d); }
  rational operator*(rational r) const { return rational(n * r.n, d * r.d); }
  rational operator/(rational r) const { return rational(n * r.d, d * r.n); }

  rational operator+=(const rational &r) { return *this = *this + r; }
  rational operator-=(const rational &r) { return *this = *this - r; }
  rational operator*=(const rational &r) { return *this = *this * r; }
  rational operator/=(const rational &r) { return *this = *this / r; }

  explicit operator double() const { return (double) n / d; }

  ll num() const { return n; }
  ll den() const { return d; }
};

/************************/
/* integer/modratio.cpp */
/************************/

class modratio {
  ll n, d;

public:
  modratio(): n(0), d(1) {}
  modratio(ll _n): n((_n + MOD) % MOD), d(1) {}
  modratio(ll _n, ll _d): n((_n + MOD) % MOD), d((_d + MOD) % MOD) {}

  modratio operator+(modratio r) const { return modratio(n * r.d + d * r.n, d * r.d); }
  modratio operator-(modratio r) const { return modratio(n * r.d - d * r.n, d * r.d); }
  modratio operator*(modratio r) const { return modratio(n * r.n, d * r.d); }
  modratio operator/(modratio r) const { return modratio(n * r.d, d * r.n); }

  ll num() const { return n; }
  ll den() const { return d; }

  ll value() const { // n * d^-1 % MOD
    ll t = MOD - 2, p = 1, q = d;
    while(t > 0) {
      if(t % 2) p = (p * q) % MOD;
      q = (q * q) % MOD;
      t /= 2;
    }
    return n * (p % MOD) % MOD;
  }
};

/********************************/
/* integer/next_combination.cpp */
/********************************/

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

/****************************************/
/* integer/next_pertial_permutation.cpp */
/****************************************/

template <class BI>
bool next_partial_permutation(BI first, BI middle, BI last) {
  reverse(middle, last);
  return next_permutation(first, last);
}

/*****************/
/* math/dice.cpp */
/*****************/

/* 1が上面, 2が前面にあるとき, その右がわの面には3が来るようなサイコロ対象 */
struct dice { int f, l, b, r, t, d; };

/* 2つの隣接する面に対して, その左に位置する面の値 */
int third_face[7][7] = {
  { 0, 0, 0, 0, 0, 0, 0, },
  { 0, 0, 4, 2, 5, 3, 0, },
  { 0, 3, 0, 6, 1, 0, 4, },
  { 0, 5, 1, 0, 0, 6, 2, },
  { 0, 2, 6, 0, 0, 1, 5, },
  { 0, 4, 0, 1, 6, 0, 3, },
  { 0, 0, 3, 5, 2, 4, 0, },
};

/* 上面と前面の値からサイコロを初期化する */
void init(dice &m, int t, int f) {
  m.t = t; m.f = f; m.l = third_face[t][f]; m.d = 7 - m.t; m.b = 7 - m.f; m.r = 7 - m.l;
}

/* 0: 前面, 1: 左面, 2: 後面, 3: 右面, 4: 上面, 6: 下面の値 */
int dice_number(dice &m, int k) {
  switch(k) {
    case 0: return m.f;
    case 1: return m.l;
    case 2: return m.b;
    case 3: return m.r;
    case 4: return m.t;
    case 5: return m.d;
  }
  return -1;
}

/* 0: 前, 1: 左, 2: 後, 3: 右に回転 */
void dice_roll(dice &m, int k) {
  int tmp;
  switch(k) {
    case 0: tmp = m.f; m.f = m.t; m.t = m.b; m.b = m.d; m.d = tmp; break;
    case 1: tmp = m.l; m.l = m.t; m.t = m.r; m.r = m.d; m.d = tmp; break;
    case 2: tmp = m.b; m.b = m.t; m.t = m.f; m.f = m.d; m.d = tmp; break;
    case 3: tmp = m.r; m.r = m.t; m.t = m.l; m.l = m.d; m.d = tmp; break;
  }
}

/************************/
/* matrix/hungarian.cpp */
/************************/

template <typename T> T hungarian(const vector< vector<T> > &a, ll n) {
  const ll INF = 1LL << 60;
  vector<ll> fx(n, INF), fy(n, 0), x(n, -1), y(n, -1);
  ll p, q;

  REP(i, 0, n) REP(j, 0, n) fx[i] = max(fx[i], a[i][j]);

  for(ll i = 0; i < n;) {
    vector<ll> t(n, -1), s(n + 1, i);
    for(p = q = 0; p <= q && x[i] < 0; p++) {
      for(ll k = s[p], j = 0; j < n && x[i] < 0; j++) {
        if(fx[k] + fy[j] == a[k][j] && t[j] < 0) {
          s[++q] = y[j], t[j] = k;
          if(s[q] < 0) for(p = j; p >= 0; j = p) y[j] = k = t[j], p = x[k], x[k] = j;
        }
      }
    }
    if(x[i] < 0) {
      T d = INF;
      REP(k, 0, q + 1) REP(j, 0, n) if(t[j] < 0) d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
      REP(j, 0, n) fy[j] += (t[j] < 0 ? 0 : d);
      REP(k, 0, q + 1) fx[s[k]] -= d;
    } else i++;
  }

  T ret = 0;
  REP(i, 0, n) ret += a[i][x[i]];

  return ret;
}

/********************/
/* string/split.cpp */
/********************/

vector<string> split(string s, string p) {
  vector<string> ret;
  ll h = 0;

  REP(i, 0, s.size() - p.size() + 1) if(s.substr(i, p.size()) == p) {
    ret.push_back(s.substr(h, i - h));
    h = i + p.size();
    i += (ll) p.size() - 1;
  }
  ret.push_back(s.substr(h, (ll) s.size() - h));

  return ret;
}

/***************************/
/* string/suffix_array.cpp */
/***************************/

vector<ll> suffix_array(const string &S) {
  ll n = S.length(), k = 1;
  vector<ll> sa(n + 1), rnk(n + 1), tmp(n + 1);

  auto compare_sa = [&](const ll& i, const ll& j) {
    if(rnk[i] != rnk[j]) return rnk[i] < rnk[j];
    ll ri = i + k <= n ? rnk[i + k] : -1;
    ll rj = j + k <= n ? rnk[j + k] : -1;
    return ri < rj;
  };

  REP(i, 0, n + 1) sa[i] = i;
  REP(i, 0, n + 1) rnk[i] = i < n ? S[i] : -1;

  for(; k <= n; k *= 2) {
    sort(sa.begin(), sa.end(), compare_sa);
    tmp[sa[0]] = 0;
    REP(i, 1, n + 1) tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
    REP(i, 0, n + 1) rnk[i] = tmp[i];
  }

  return sa;
}

/***************************/
/* string/aho_corasick.cpp */
/***************************/

class PMA {
  PMA* next[256];
  vector<ll> matched;

  PMA() { REP(i, 0, 256) next[i] = NULL; }

  void build(vector<string> &p) {
    REP(i, 0, 256) next[i] = NULL;
    this->next[0] = this;
    REP(i, 0, p.size()) {
      PMA *now = this;
      REP(j, 0, p[i].length()) {
        if(now->next[p[i][j]] == 0) now->next[p[i][j]] = new PMA;
        now = now->next[p[i][j]];
      }
      now->matched.push_back(i);
    }

    queue<PMA*> q;
    REP(i, 1, 256) {
      if(!this->next[i]) this->next[i] = this;
      else {
        this->next[i]->next[0] = this;
        q.push(this->next[i]);
      }
    }

    while(!q.empty()) {
      PMA *now = q.front();
      q.pop();
      REP(i, 1, 256) if(now->next[i]){
        PMA *nxt = now->next[0];
        while(!nxt->next[i]) nxt = nxt->next[0];
        now->next[i]->next[0] = nxt->next[i];
        vector<ll> &m1 = now->next[i]->matched, &m2 = nxt->next[i]->matched;
        REP(j, 0, m2.size()) if(!binary_search(m1.begin(), m1.end(), m2[j])) m1.push_back(m2[j]);
        sort(m1.begin(), m1.end());
        q.push(now->next[i]);
      }
    }
  }

public:
  /* initialized by C-array of pattern string */
  PMA(string *parray, ll n) {
    vector<string> p;
    REP(i, 0, n) p.push_back(parray[i]);
    build(p);
  }

  /* initialized by vector of pattern string */
  PMA(vector<string> &p) {
    build(p);
  }

  /* find all substring mathing pattern */
  vector< vector<ll> > match(string s) {
    vector< vector<ll> > idx(s.length());
    PMA* pma = this;
    REP(i, 0, s.length()) {
      while(!pma->next[s[i]]) pma = pma->next[0];
      pma = pma->next[s[i]];
      for(ll j : pma->matched) idx[i].push_back(j);
    }
    return idx;
  }
};

/***************************/
/* string/rolling_hash.cpp */
/***************************/

class RollingHash {
public:
  const ll B = 1009, MOD1 = 1000000007, MOD2 = 1000000009;

private:
  ll n;
  vector<ll> p1, p2, h1, h2;

public:
  RollingHash(const string &s): n(s.length()), p1(n + 1), p2(n + 1), h1(n + 1), h2(n + 1) {
    p1[0] = p2[0] = 1;
    REP(i, 0, n) p1[i + 1] = (p1[i] * B) % MOD1;
    REP(i, 0, n) p2[i + 1] = (p2[i] * B) % MOD2;
    h1[0] = h2[0] = 0;
    REP(i, 0, n) h1[i + 1] = (h1[i] * B + s[i]) % MOD1;
    REP(i, 0, n) h2[i + 1] = (h2[i] * B + s[i]) % MOD2;
  }

  ll hash(ll l, ll r) {
    ll x1 = (h1[r] - (h1[l] * p1[r - l] % MOD1) + MOD1) % MOD1;
    ll x2 = (h2[r] - (h2[l] * p2[r - l] % MOD2) + MOD2) % MOD2;
    return x1 * MOD2 + x2;
  }
};
