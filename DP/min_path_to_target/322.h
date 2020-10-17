#include "basic.h"

/*

给定硬币的几种面额coins
每种面额有无限个硬币
选择最少的硬币个数, 使之和等于amount
不存在解法时返回-1

# example:
> coins = [1,2,5], amount = 11
ans: 3
11 = 1 + 5 + 5

> coins = [2], amount = 3
ans: -1


# 递归解法（回溯法）
f(amount) = 1 + min{ i:[1,N] }{ f(amount - coins[i]) }

递归问题转成动态规划的一个思路
  递归 -> 含有重复子问题 -> 记忆式搜索(自顶向下) -> 动态规划(自底向上)

*/


int coinChange(const vector<int>& coins, int amount) {
  const int coin_kind_n = (int)coins.size();

  vector<int> ans(amount + 1);
  for (int i = 1; i <= amount; i++) {
    int ret = -1;
    for (int c : coins) {
      if (i >= c && ans[i-c] >= 0)
        if (ret < 0 || ans[i-c] + 1 < ret)
          ret = ans[i-c] + 1;
    }
    ans[i] = ret;
  }
  return ans[amount];
}


void test() {
  assert_eq(3, coinChange({1,2,5}, 11));
  assert_eq(-1, coinChange({2}, 3));
}