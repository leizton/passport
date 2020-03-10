#include "basic.h"

/*

# 最长不重复子串
给定一个字符串，找出其中不含有重复字符的最长子串的长度

# example
"abcabcbb"
  => 3

*/

int lengthOfLongestSubstring(string&& s) {
  if (s.empty()) return 0;
  const int s_len = (int)s.length();
  int char_to_idx[256];
  std::fill(std::begin(char_to_idx), std::end(char_to_idx), -1);

  int max_len = 1;
  int cur_len = 1, start = 0;
  char_to_idx[s[0] + 128] = 0;

  for (int i = 1; i < s_len; i++) {
    if (char_to_idx[s[i] + 128] < 0) {
      cur_len++;
      char_to_idx[s[i] + 128] = i;
    } else {
      max_len = std::max(max_len, cur_len);
      int prev_idx = char_to_idx[s[i] + 128];
      for (; start < prev_idx; start++)
        char_to_idx[s[start] + 128] = -1;
      //
      cur_len = i - prev_idx;
      start = prev_idx + 1;
      char_to_idx[s[i] + 128] = i;
    }
  }
  return std::max(max_len, cur_len);
}
