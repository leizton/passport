#include "basic.h"

/*

# 最小编辑距离

*/

int minDistance(string word1, string word2) {
  if (word1.empty() || word2.empty()) {
    return (int)std::max(word1.length(), word2.length());
  }

  const int n1(word1.length() + 1), n2(word2.length() + 1);
  const char *s1(word1.c_str()-1), *s2(word2.c_str()-1);

  // alloc
  int** mat = new int*[n1];
  for (int i = 0; i < n1; i++) {
    mat[i] = new int[n2];
  }

  for (int i = 0; i < n1; i++) {
    mat[i][0] = i;
  }
  for (int j = 0; j < n2; j++) {
    mat[0][j] = j;
  }
  for (int j = 1; j < n2; j++) {
    for (int i = 1; i < n1; i++) {
      int t = std::min(mat[i-1][j]+1, mat[i][j-1]+1);
      mat[i][j] = std::min(t, mat[i-1][j-1] + (s1[i]==s2[j] ? 0 : 1));
    }
  }
  int ret = mat[n1-1][n2-1];

  // free
  for (int i = 0; i < n1; i++) {
    delete[] mat[i];
    mat[i] = nullptr;
  }
  delete[] mat;
  mat = nullptr;
  return ret;
}

void test() {
  assert_eq(0, minDistance("", ""));
  assert_eq(3, minDistance("abc", ""));
  assert_eq(5, minDistance("abc123ca", "a5cd423cbd"));
}
