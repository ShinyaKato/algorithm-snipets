#include <iostream>
#include <cmath>
#define REP(i, a, n) for(int i = (a); i < (n); i++)
using namespace std;

struct point { double x, y; };
struct line { point p, q; };

double distance(line l, point p) {
  double x0 = p.x, y0 = p.y;
  double x1 = l.p.x, y1 = l.p.y;
  double x2 = l.q.x, y2 = l.q.y;
  double a = x2 - x1;
  double b = y2 - y1;
  double a2 = a * a;
  double b2 = b * b;
  double r2 = a2 + b2;
  double tt = -(a*(x1 - x0) + b*(y1 - y0));
  if(tt < 0) return sqrt((x1 - x0)*(x1-x0) + (y1 - y0)*(y1-y0));
  if(tt > r2) return sqrt((x2 - x0)*(x2 - x0) + (y2 - y0)*(y2 - y0));
  double f1 = a*(y1 - y0) - b*(x1 - x0);
  return sqrt((f1*f1)/r2);
}

int main(void) {
  point p = (point) { 1, 6 };
  line l = (line) { (point) { 2, 5 }, (point) { -1, 1 } };

  cout << distance(l, p) << endl;

  return 0;
}
