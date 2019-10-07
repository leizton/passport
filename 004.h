#include "basic.h"

/*

# 两个有序数组中位数

给定两个有序数组，在O(log(m+n))内找出两个数组的中位数

# ex
[1,3] [2] => 2
[1,3] [2,4] => 2.5

*/

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
  if (nums1.empty() && nums2.empty()) {
    return 0.;
  }

  const size_t N1 = nums1.size(), N2 = nums2.size();
  const size_t N = N1 + N2;
  const bool has_two_target = ((N%2) == 0);
  const size_t target = has_two_target ? (N/2-1) : (N/2);
  size_t p1 = 0, p2 = 0, pos = 0;
  int v;

  while (p1 < N1 && p2 < N2) {
    if (nums1[p1] <= nums2[p2]) {
      v = nums1[p1++];
    } else if (nums1[p1] > nums2[p2]) {
      v = nums2[p2++];
    }

    if (pos == target) {
      if (!has_two_target) {
        return v;
      }
      if (p1 < N1 && p2 < N2) {
        v += std::min(nums1[p1], nums2[p2]);
      } else if (p1 < N1) {
        v += nums1[p1];
      } else if (p2 < N2) {
        v += nums2[p2];
      }
      return v / 2.0;
    }

    pos++;
  }

  vector<int>* nums3 = p1 < N1 ? &nums1 : &nums2;
  p1 = p1 < N1 ? p1 : p2;
  p1 += target - pos;
  if (!has_two_target) {
    return (*nums3)[p1];
  } else {
    return ( (*nums3)[p1] + (*nums3)[p1+1] ) / 2.0;
  }
}

void test(vector<int>&& nums1, vector<int>&& nums2) {
  vector<int> v1(nums1), v2(nums2);
  double ret = findMedianSortedArrays(v1, v2);
  print(ret);
}

void test() {
  test({1,3}, {2});  // 2
  test({2}, {1,3});  // 2
  test({}, {1,2,3});  // 2
  test({1,3}, {2,4});  // 2.5
  test({1,2,3,4}, {});  // 2.5
  test({1}, {1});  // 1
  test({1}, {2});  // 1.5
  test({1}, {});  // 1
  test({}, {2});  // 2
}
