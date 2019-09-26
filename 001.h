#include "basic.h"

/*

在给定数组中找出和为目标值的那两个整数

--> ex
给定 nums = [11, 2, 15, 7], target = 9
因为 nums[1] + nums[3] = 2 + 7 = 9
所以返回 [1, 3]

*/

vector<int> twoSum(vector<int>& nums, int target) {
  unordered_map<int, size_t> valToIdx;
  for (size_t i = 0; i < nums.size(); i++) {
    valToIdx[nums[i]] = i + 1;
  }

  vector<int> ret;
  for (size_t i = 0; i < nums.size(); i++) {
    int another = target - nums[i];
    size_t idx = valToIdx[another];
    if (idx > 0 && idx != i+1) {
      // [[warn]] 不能是自己和自己的相加
      ret.push_back(i);
      ret.push_back(idx-1);
      return ret;
    }
  }
  return ret;
}

void test() {
  vector<int> nums{11, 2, 15, 7};
  auto ret = twoSum(nums, 9);
  printer.print(ret);

  nums = {3, 2, 4};
  ret = twoSum(nums, 6);
  printer.print(ret);
}
