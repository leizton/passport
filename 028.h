#include "basic.h"

/*

# strstr

查找子串位置

sunday算法

*/

int strStr(string str, string target) {
  const char* s = str.c_str();
  const char* t = target.c_str();
  const int N1=(int)str.length(), N2=(int)target.length();
  const int N = N1 - N2;

  int pos[256];
  for (int i = 0; i < 256; i++) {
    pos[i] = -1;
  }
  for (int i = 0; i < N2; i++) {
    pos[int(t[i]) + 128] = i;
  }

  for (int p = 0; p <= N; ) {
    int q = 0;
    for (int i = p; q<N2 && s[i++]==t[q]; q++);
    if (q >= N2) return p;

    int i = p+N2;
    if (i >= N1) return -1;
    i = pos[int(s[i]) + 128];
    if (i < 0) {
      p += N2+1;
    } else {
      p += N2-i;
    }
  }
  return -1;
}

void test() {
  print(strStr("", ""));  // 0
  print(strStr("abc", ""));  // 0
  print(strStr("", "a"));  // -1
  print(strStr("abc123", "c1"));  // 2
  print(strStr("abc123", "a1"));  // -1
}
