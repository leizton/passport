#include "basic.h"


/*

使用最小花费爬楼梯

每次往上一层或两层
类似斐波拉契数列

*/


int minCostClimbingStairs(vector<int>&& cost) {
  const int n = cost.size();
  if (n < 2) return 0;
  for (int i = 2; i < n; i++) {
    cost[i] += std::min(cost[i-1], cost[i-2]);
  }
  return std::min(cost[n-1], cost[n-2]);
}


void test() {
  assert_eq(15, minCostClimbingStairs({10, 15, 20}));
  assert_eq(6, minCostClimbingStairs({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}));
}