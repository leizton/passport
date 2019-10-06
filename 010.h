#include "basic.h"

/*

# 正则表达式匹配

输入s是原文, p是正则表达式
需要处理p中的 . *

# ex
("aa", "a") => false
("aa", "a.") => true
("aa", "a*") => true

#
动态规划

*/

// 对 pattern 简化
void simplifyPattern(string& pattern) {
  if (pattern.length() < 4) return;
  const int N1 = int(pattern.length()-1);
  char* p = pattern.data();
  int j = 0;
  bool flag = false;
  for (int i = 0; i <= N1; ) {
    if (i < N1 && p[i+1] == '*') {
      if (flag) {
        if (p[i] == p[j-2]) {
          i += 2;
        } else {
          p[j++] = p[i++];
          p[j++] = p[i++];
        }
      } else {
        p[j++] = p[i++];
        p[j++] = p[i++];
        flag = true;
      }
    } else {
      p[j++] = p[i++];
      flag = false;
    }
  }
  pattern.resize(j);
}

void matchOneChar(const char* s, const int s_len, char c,
                  vector<int>& buf1, vector<int>& buf2)
{
  for (int i : buf1) {
    if (i+1 < s_len && (c == '.' || s[i+1] == c)) {
      buf2.push_back(i+1);
    }
  }
}

void matchMultiChar(const char* s, const int s_len, char c,
                    vector<int>& buf1, vector<int>& buf2)
{
  for (int i : buf1) {
    if (!buf2.empty() && i <= buf2.back()) {
      continue;
    }
    buf2.push_back(i);
    for (int j = i+1; j < s_len; j++) {
      if (c == '.' || s[j] == c) {
        buf2.push_back(j);
      } else {
        break;
      }
    }
  }
}

bool isMatch(string src, string pattern) {
  if (pattern.empty()) return src.empty();

  simplifyPattern(pattern);  // 可选
  src = "a" + src;
  pattern = "a" + pattern;
  const int s_len = (int)src.length();
  const int p_len = (int)pattern.length();
  const char* s = src.c_str();
  const char* p = pattern.c_str();

  vector<int> buf1, buf2;
  buf1.push_back(0);
  for (int i = 1; i < p_len;) {
    if (i < p_len-1 && p[i+1] == '*') {
      matchMultiChar(s, s_len, p[i], buf1, buf2);
      i += 2;
    } else {
      matchOneChar(s, s_len, p[i], buf1, buf2);
      i++;
    }
    if (buf2.empty()) {
      return false;
    }
    buf1.clear();
    buf1.swap(buf2);
  }
  return !buf1.empty() && buf1.back() >= s_len-1;
}

void testSimplifyPattern() {
  string p = "aba*ca*a*.*c*d";
  simplifyPattern(p);
  printer.print(p);
  p = "aba*ca*d*";
  simplifyPattern(p);
  printer.print(p);
}

void test() {
  printer.print(isMatch("abcadaaac", "ab.ada*ac"));  // true
  printer.print(isMatch("abcadaaac", "ab.ada*a"));  // false
  printer.print(isMatch("abcadaaac", ".*c"));  // true
  printer.print(isMatch("abcadaaaa", "ab.ada*ac"));  // false
  printer.print(isMatch("abcadaaaa", "ab.ada*aa"));  // true
  printer.print(isMatch("a", "a*"));  // true
  printer.print(isMatch("", "a*"));  // true

  printer.print(isMatch("bccbbabcaccacbcacaa", ".*b.*c*.*.*.c*a*.c"));  // false
  printer.print(isMatch("bccbbabcaccacbcacaa", ".*b.*c*.*.c*a*."));  // true

  printer.print(isMatch("ccbbabbbabababa", ".*.ba*c*c*aab.a*b*"));  // false

  printer.print(isMatch("mississippi", "mis*is*p*."));  // false
  printer.print(isMatch("mississippi", "mis*is*p*..*"));  // true
}
