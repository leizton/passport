#include "basic.h"

/*

# 最长不重复子串

给定一个字符串，找出其中不含有重复字符的最长子串的长度

*/

int lengthOfLongestSubstring(string&& s) {
  if (s.empty()) return 0;

  int flag[256];
  for (int i = 0; i < 256; i++) {
    flag[i] = -1;
  }
  const int slen = (int)s.length();

  int max_len = 1, start = 0, pos;
  flag[s[start]] = start;
  for (int i = 1; i < slen; i++) {
    pos = flag[s[i]];
    flag[s[i]] = i;

    if (pos < start) {
      continue;
    }

    if (i-start > max_len) {
      max_len = i-start;
    }
    start = pos+1;
  }
  if (slen-start > max_len) {
    max_len = slen-start;
  }
  return max_len;
}

void test() {
  int ret;

  ret = lengthOfLongestSubstring("bbbbb");  // 1
  print(ret);

  ret = lengthOfLongestSubstring("bbabb");  // 2
  print(ret);

  ret = lengthOfLongestSubstring("pwwkew");  // 3
  print(ret);
}
