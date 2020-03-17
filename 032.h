#include "basic.h"

/*

# 最长有效括号子串

# ex
(() => 2
)()()) => 4

*/

int longestValidParentheses(string str) {
  const int N = (int)str.length();
  const int N1 = N - 1;
  const char* s = str.c_str();

  int ret = 0;
  vector<pair<int,int>> cand1, cand2;  // candidates
  for (int i = 0; i < N-1; i++) {
    if (s[i] == '(' && s[i+1] == ')') {
      cand1.emplace_back(i, i+1);
      ret = 2;
    }
  }

  bool changed = true;
  while (cand1.size() >= 1 && changed) {
    changed = false;

    // extend cand1
    for (auto& p : cand1) {
      int i = p.first, j = p.second;
      while (p.first > 0 && p.second < N1 && s[p.first-1]=='(' && s[p.second+1]==')') {
        p.first -= 1;
        p.second += 1;
        ret = std::max(ret, p.second-p.first+1);
        changed = true;
      }
    }

    // merge to cand2
    cand2.push_back(cand1.front());
    for (int i = 1, j = 0; i < cand1.size(); i++) {
      if (cand1[i].first == cand2[j].second + 1) {
        cand2[j].second = cand1[i].second;
        ret = std::max(ret, cand2[j].second-cand2[j].first+1);
        changed = true;
      } else {
        cand2.push_back(cand1[i]);
        j++;
      }
    }

    cand1.clear();
    cand1.swap(cand2);
  }

  return ret;
}

void test() {
  assert_eq(0, longestValidParentheses(""));
  assert_eq(0, longestValidParentheses("(("));
  assert_eq(2, longestValidParentheses("(()"));
  assert_eq(4, longestValidParentheses(")()())"));
  assert_eq(4, longestValidParentheses("()()"));
  assert_eq(6, longestValidParentheses("()(())"));
  assert_eq(22, longestValidParentheses(")(((((()())()()))()(()))("));
  assert_eq(2, longestValidParentheses("()(()"));
}
