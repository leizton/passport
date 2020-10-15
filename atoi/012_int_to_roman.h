#include "basic.h"

/*

整数转罗马数字

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

*/

string intToRoman(int num) {
  int a = num / 1000; // 千位
  num -= a * 1000;
  int b = num / 100; // 百位
  num -= b * 100;
  int c = num / 10;
  int d = num - c * 10;

  char ret[16];
  int p = 0;

  for (int i = 0; i < a; i++) ret[p++] = 'M';

  auto f = [&ret, &p](int v, char c1, char c2, char c3) {
    if (v < 4) {
      for (int i = 0; i < v; i++) ret[p++] = c1;
    } else if (v == 4) {
      ret[p++] = c1;
      ret[p++] = c2;
    } else if (v < 9) {
      ret[p++] = c2;
      for (int i = 5; i < v; i++) ret[p++] = c1;
    } else {
      ret[p++] = c1;
      ret[p++] = c3;
    }
  };
  f(b, 'C', 'D', 'M');
  f(c, 'X', 'L', 'C');
  f(d, 'I', 'V', 'X');

  ret[p] = 0;
  return ret;
}

void test() {
  assert_eq("MCMXCIV", intToRoman(1994));
}