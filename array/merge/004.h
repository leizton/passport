#include "basic.h"

/*

# 两个有序数组中位数
给定两个有序数组，在O(log(m+n))内找出两个数组的中位数
时间复杂度O(logn), 空间O(1)

# example
[1,3] [2] ⇒ 2
[1,3] [2,4] ⇒ 2.5

# solu
设 a[0:m) b[0:n) 有序
把 a b 归并排序得到 c[0:N), N=m+n
取 p = (m+n)>>1
返回值 = {
  N是奇数, ⇒ c[p]
  N是偶数, ⇒ (c[p-1]+c[p])/2.0
  特别地, 当p=0, → N=1, → ret=c[p]
}

*/

double findMedianSortedArrays(vector<int> a, vector<int> b) {
  const int m = a.size(), n = b.size();
  const int pos = ((m + n) >> 1);
  const bool is_odd = ((m + n) & 1);

  int cp1 = INT_MIN, cp = INT_MIN;
  int ia = 0, ib = 0;

  for (int i = 0; i <= pos; i++) {
    // 把小的那个指针向后移动一位
    cp1 = cp;
    cp = (ia < m && (ib >= n || a[ia] < b[ib])) ? a[ia++] : b[ib++];
  }
  return is_odd ? cp : (cp + cp1) / 2.0;
}

void test() {
  assert_eq(2.0, findMedianSortedArrays({1, 3}, {2}));
  assert_eq(2.0, findMedianSortedArrays({2}, {1, 3}));
  assert_eq(2.0, findMedianSortedArrays({}, {1, 2, 3}));
  assert_eq(2.5, findMedianSortedArrays({1, 3}, {2, 4}));
  assert_eq(2.5, findMedianSortedArrays({1, 2, 3, 4}, {}));
  assert_eq(1.0, findMedianSortedArrays({1}, {1}));
  assert_eq(1.5, findMedianSortedArrays({1}, {2}));
  assert_eq(2.5, findMedianSortedArrays({1}, {2, 3, 4}));
}
