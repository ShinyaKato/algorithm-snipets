#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

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

int main(void) {
  const double EPS = 1e-8;

  REP(i, 0, 300) {
    Point2 l1((double) (rand() % 100), (double) (rand() % 100));
    Point2 l2((double) (rand() % 100), (double) (rand() % 100));
    double t = 0.5 + (double) (rand() % 201 - 100) / 100;
    Point2 h = l1 * t + l2 * (1 - t);
    Point2 n = Vector2((l2 - l1).y, -(l2 - l1).x).normalize();
    double s = (double) (rand() % 201 - 100) / 100;
    Point2 p = h + n * s;
    double d = point_to_line_distance(p, l1, l2);
    assert(abs(d - abs(s)) < EPS);
  }

  // point_to_line_segment_distance
  REP(i, 0, 300) {
    Point2 l1((double) (rand() % 100), (double) (rand() % 100));
    Point2 l2((double) (rand() % 100), (double) (rand() % 100));
    if(0 <= i && i < 100) {
      double t = (double) (rand() % 101) / 100;
      Point2 h = l1 * t + l2 * (1 - t);
      Point2 n = Vector2((l2 - l1).y, -(l2 - l1).x).normalize();
      double s = (double) (rand() % 201 - 100) / 100;
      Point2 p = h + n * s;
      double d = point_to_line_segment_distance(p, l1, l2);
      assert(abs(d - abs(s)) < EPS);
    }
    if(100 <= i && i < 200) {
      double t = 1 + (double) (rand() % 101) / 100;
      Point2 h = l1 * t + l2 * (1 - t);
      Point2 n = Vector2((l2 - l1).y, -(l2 - l1).x).normalize();
      double s = (double) (rand() % 201 - 100) / 100;
      Point2 p = h + n * s;
      double d = point_to_line_segment_distance(p, l1, l2);
      assert(abs(d - p.distance(l1)) < EPS);
    }
    if(200 <= i && i < 300) {
      double t = -(double) (rand() % 101) / 100;
      Point2 h = l1 * t + l2 * (1 - t);
      Point2 n = Vector2((l2 - l1).y, -(l2 - l1).x).normalize();
      double s = (double) (rand() % 201 - 100) / 100;
      Point2 p = h + n * s;
      double d = point_to_line_segment_distance(p, l1, l2);
      assert(abs(d - p.distance(l2)) < EPS);
    }
  }

  // lines_intersect_point
  REP(i, 0, 100) {
    Point2 p, a, b, c, d;
    do {
      p = Vector2((double) (rand() % 100), (double) (rand() % 100));
      a = Vector2((double) (rand() % 100), (double) (rand() % 100));
      c = Vector2((double) (rand() % 100), (double) (rand() % 100));
      b = a + (p - a) * (double) (rand() % 5 + 1);
      d = c + (p - c) * (double) (rand() % 5 + 1);
    } while(abs((b - a).det(d - c)) < EPS);
    Point2 q = lines_intersect_point(a, b, c, d);
    assert(p.distance(q) < EPS);
  }
}
