#include "basic.h"

/*

# strstr

查找子串位置

*/

struct Result {
  int idx;
  int cmp_cnt;
};

Result sunday(string str, string pattern) {
  if (pattern.empty()) return {0, 0};
  if (str.length() < pattern.length()) return {-1, 0};
  const char* a = pattern.c_str();
  const char* b = str.c_str();
  const int n1 = (int)pattern.length();
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
  const char* b1;
  int k, cmp_cnt=0;
  for (int p = 0; p <= limit; ) {
    b1 = b + p;
    for (k = 0; k<n1 && a[k]==b1[k]; k++);
    cmp_cnt += k+1;
    if (k == n1) return {p, cmp_cnt};
    if (p == limit) return {-1, cmp_cnt};
    p += n1 - last_idx[ b1[n1] + 128 ];
  }
  return {-1, cmp_cnt};
}

int strStr(string str, string pattern) {
  cout << "\n>> " << str.length() << " " << pattern.length() << endl;

  Result sdy_ret = sunday(str, pattern);
  cout << "sunday: " << sdy_ret.cmp_cnt << endl;

  return sdy_ret.idx;
}

void test() {
  ASSERT_EQ(0, strStr("", ""));
  ASSERT_EQ(0, strStr("abc", ""));
  ASSERT_EQ(-1, strStr("", "a"));
  ASSERT_EQ(2, strStr("abc123", "c1"));
  ASSERT_EQ(-1, strStr("abc123", "a1"));
  ASSERT_EQ(1, strStr("aabaabbbaabbbbabaaab", "abaa"));
  ASSERT_EQ(10, strStr("bbbbbbbbbbbbbbbbbbb1", "bbbbbbbbb1"));
}
