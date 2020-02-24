#include "basic.h"

/*

# 移除元素
给定一个数组nums和一个值val, 你需要原地移除所有数值等于val的元素, 并返回移除后数组的新长度
空间复杂度O(1)
元素的顺序可以改变. 你不需要考虑数组中超出新长度后面的元素

# ex
给定 nums = [3,1,2,3], val = 3
  返回2, nums前两个元素是[1, 2], 顺序随意, 后面的元素随意

#
类似快排分partition的做法
(==val)的是一个partition, (!=val)的是另一个partition

*/

int removeElement(vector<int>& nums, int val) {
  int p = 0, last = nums.size(), t;
  while (p < last) {
    if (nums[p] == val) {
      for (last--; last > p && nums[last] == val; last--);
      if (last > p) {
        t = nums[p];
        nums[p] = nums[last];
        nums[last] = t;
      }
    }
    p++;
  }
  nums.resize(last);
  return last;
}

void test() {
  vector<int> v1 = {3,1,2,3};
  ASSERT_EQ(2, removeElement(v1, 3));
  print(v1);
}
