#include <iostream>
#include <cmath>
#define REP(i, a, n) for(int i = (a); i < (n); i++)
using namespace std;

struct point { double x, y; };
struct line { point p, q; };

bool intersect(line l1, line l2) {
  double ax = l1.p.x, ay = l1.p.y;
  double bx = l1.q.x, by = l1.q.y;
  double cx = l2.p.x, cy = l2.p.y;
  double dx = l2.q.x, dy = l2.q.y;
  double ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
  double tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
  double tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
  double td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);
  return tc * td < 0 && ta * tb < 0;
}

int main(void) {
  line l1 = (line) { (point) { 2, 5 }, (point) { -2, 1 } };
  line l2 = (line) { (point) { 0, 0 }, (point) { -1, 2 } };
  cout << intersect(l1, l2) << endl;

  line l3 = (line) { (point) { -1, 0 }, (point) { 1, 0 } };
  line l4 = (line) { (point) { 0, 2 }, (point) { 0, 1 } };
  cout << intersect(l3, l4) << endl;

  return 0;
}
