#include "basic.h"


/*

给定目标楼层n，每次爬一层或两层
有多少种爬楼梯的方法

斐波拉契数列

*/


int climbStairs(int n) {
  int prev1 = 1, prev2 = 1, t;
  for (int i = 2; i <= n; i++) {
    t = prev2;
    prev2 = prev1 + prev2;
    prev1 = t;
  }
  return prev2;
}