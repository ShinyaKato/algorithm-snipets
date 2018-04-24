#include <bits/stdc++.h>
#define REP(i, a, n) for(ll i = ((ll) a); i < ((ll) n); i++)
using namespace std;
typedef long long ll;

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

int main(void) {
}
