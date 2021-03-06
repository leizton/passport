#include "basic.h"

/*

# 盛最多水的容器

依次给出n个非负整数, 每个整数代表一根柱子
两根柱子围成的面积 = 距离 * 短柱子的长度, area(p,q) = (q-p) * min(h[p],h[q])
找出最大的面积

#
双指针
移动更短的那个指针
考虑[p,q]。下一步可行的是 [p+1,q] [p,q-1]
设 h[p] < h[q] => area(p,q) = h[p] * (q-p)
area(p,q-1) <= h[p] * (q-1-p) < area(p,q), 所以选择 area(p+1,q)

*/

int maxArea(const vector<int>& h) {
  if (h.size() < 2) return 0;

  int max_area = 0;
  int p = 0, q = (int)h.size()-1;
  while (q > p) {
    int area = (q-p) * std::min(h[p], h[q]);
    max_area = std::max(max_area, area);

    if (h[p] < h[q])
      p++;
    else
      q--;
  }
  return max_area;
}

void test() {
  assert_eq(49, maxArea({1,8,6,2,5,4,8,3,7}));
}
