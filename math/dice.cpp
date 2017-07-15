/*************************
 * dice.cpp
 *************************/

#include <iostream>
using namespace std;

/**
 * 1が上面, 2が前面にあるとき, その右がわの面には3が来るようなサイコロ対象
 */
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

int main(void) {
  dice m;
  init(m, 1, 2);
  cout << dice_number(m, 4) << " expected 1" << endl;
  cout << dice_number(m, 3) << " expected 3" << endl;
  dice_roll(m, 2);
  cout << dice_number(m, 4) << " expected 2" << endl;
  cout << dice_number(m, 3) << " expected 3" << endl;
  dice_roll(m, 3);
  cout << dice_number(m, 4) << " expected 4" << endl;
  cout << dice_number(m, 3) << " expected 2" << endl;

  return 0;
}
