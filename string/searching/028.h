#include "basic.h"

/*

# strstr

查找子串位置

sunday算法

*/

int strStr(string str, string target) {
  if (target.empty()) return 0;
  if (str.length() < target.length()) return -1;
  const char* a = target.c_str();
  const char* b = str.c_str();
  const int n1 = (int)target.length();
  const int n2 = (int)str.length();

  // 记录a中每个字符最后一次出现的位置
  int last_idx[256];
  for (int i = 0; i < 256; i++) {
    last_idx[i] = -1;
  }
  for (int i = 0; i < n1; i++) {
    last_idx[ a[i] + 128 ] = i;
  }

  const int limit = n2 - n1;
  int k;
  const char* b1;
  for (int p = 0; p <= limit; ) {
    b1 = b + p;
    for (k = 0; k<n1 && a[k]==b1[k]; k++);  // 比较(k+1)次
    if (k == n1) return p;
    if (p == limit) return -1;
    p += n1 - last_idx[ b1[n1] + 128 ];
  }
  return -1;
}

void test() {
  ASSERT_EQ(0, strStr("", ""));
  ASSERT_EQ(0, strStr("abc", ""));
  ASSERT_EQ(-1, strStr("", "a"));
  ASSERT_EQ(2, strStr("abc123", "c1"));
  ASSERT_EQ(-1, strStr("abc123", "a1"));
  ASSERT_EQ(1, strStr("aabaabbbaabbbbabaaab", "abaa"));

  // m=20, n=10, cmp_n=61
  ASSERT_EQ(10, strStr("bbbbbbbbbbbbbbbbbbb1", "bbbbbbbbb1"));
}
