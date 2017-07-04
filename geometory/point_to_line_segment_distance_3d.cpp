#include <iostream>
#include <cmath>
using namespace std;

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

int main(void) {
  Point3D p = (Point3D) { 1, 6, 9 };
  Line3D l = (Line3D) { (Point3D) { 2, 5, 3 }, (Point3D) { -1, 1, 7 } };

  cout << distance(l, p) << endl;

  return 0;
}
