#include <iostream>
#include <cmath>
using namespace std;

struct point { double x, y; };
struct line { point p, q; };

double distance(line l, point p) {
  double ux = l.q.x - l.p.x;
  double uy = l.q.y - l.p.y;
  double vx = p.x - l.p.x;
  double vy = p.y - l.p.y;
  double cross = abs(ux * vy - uy * vx);
  double ul = sqrt(ux * ux + uy * uy);
  return cross / ul;
}

int main(void) {
  point p1 = (point) { 0, 0 };
  point p2 = (point) { 1, 1 };
  point p3 = (point) { 1, 3 };
  line l1 = (line) { p1, p2 };
  cout << distance(l1, p3);
}

