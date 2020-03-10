#include "basic.h"

/*

# K个不同整数的子数组
给定一个正整数数组A, 如果A的某个子数组中不同整数的个数恰好为K,
则称A的这个可以有重复元素的子数组为good_subarray

# example
A = [1,2,1,2,3], K = 2
  => 7 
恰好有2个不同整数的子数组: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

# solu
对于A的第i个元素, 以i结尾的subarr中可能有也可能没有good, 因此分成两种情况讨论

$1  ∃ {k1 k2 ...} ∈ [0 i], 使得A[k:i]都是good_subarray
  设 kmax = max{k1 k2 ...}
  ∵ ∀A[k:i]都包括A[kmax:i]的元素
  ∴ 这些good_subarray形成的集合是同一个集合S
  可用反证法证明: A[kmax]在A[kmax:i]上只出现一次
  $$1 若A[i+1]∈S
    则以(i+1)结尾且的 good_subarray 包括 {k1 k2 ...}
    $$$1 若 A[kmax] = A[i+1], 则A[kmax+1:i+1]是good, 需重新计算kmax, 因为A[kmax+1]不一定只出现一次
    $$$2 若 A[kmax] ≠ A[i+1], 则没有更多的good_subarray, 因为此时A[kmax]依然满足只出现一次
  $$2 若A[i+1]∉S
    则以(i+1)结尾的 good_subarray 不包括 {k1 k2 ...}
    则 A[kmax] ≠ A[i+1] 且 A[kmax]只出现一次
    此时移除一个旧的A[kmax], 补入一个新的A[i+1], A[kmax+1:i+1]是good
    kmax+1之后可能有更多的good_subarray, 查找方法和 $$$1 相同, 直到找到只出现一次的那个元素停止

$2  ∄ k ∈ [0 i), 使得A[k:i]是good_subarry
  从0开始查找以(i+1)结尾的good_subarray

*/

int subarraysWithKDistinct(vector<int> A, int K) {
  if (A.empty()) return 0;
  int total_good_n = 0, good_n = 0, kmax = -1;
  bool contains=false, need_refresh_kmax=false;
  vector<int> good_stat(A.size()+1, 0);
  int good_stat_n = 0;

  for (int i = 0; i < A.size(); i++) {
    need_refresh_kmax = false;
    contains = good_stat[A[i]] > 0;
    good_stat[A[i]]++;

    if (kmax >= 0) {
      if (contains) {
        if (A[kmax] == A[i]) {
          need_refresh_kmax = true;  // 此时A[kmax]不只出现一次, 所以需要更新
        }
      } else {
        good_n = 0;
        need_refresh_kmax = true;
      }
      if (need_refresh_kmax) {
        // 需要更新时A[kmax+1:i]必是good
        // 由于更新是从(kmax+1)开始, 所以移除A[kmax]
        good_stat[A[kmax]]--;
      }
    }
    else {
      if (contains || ++good_stat_n < K) {
        continue;  // 没有插入新元素 或 集合大小还不到K
      }
      need_refresh_kmax = true;
    }

    if (need_refresh_kmax) {
      for (int j = kmax+1; j <= i; j++) {
        good_n++;
        if (good_stat[A[j]] == 1) {
          kmax = j;
          break;
        }
        good_stat[A[j]]--;
      }
    }
    total_good_n += good_n;
  }
  return total_good_n;
}

void test() {
  ASSERT_EQ(7, subarraysWithKDistinct({1,2,1,2,3}, 2));
  ASSERT_EQ(23, subarraysWithKDistinct({2,2,1,2,2,2,1,1}, 2));
}
