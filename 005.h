#include "basic.h"

/*

# 最长回文子串

# ex
"babad" => "bab" or "aba"
"cbbd" => "bb"

*/

string longestPalindrome(string&& s) {
  const int N = (int)s.length();
  const int N1 = N-1;
  if (N < 2) {
    return s;
  } else if (N == 2) {
    return s[0] == s[1] ? s : s.substr(0, 1);
  }

  vector<pair<int,int>> buf1, buf2;
  for (int i = 1; i < N1; i++) {
    buf1.emplace_back(i, i);
  }
  for (int i = 0; i < N1; i++) {
    if (s[i] == s[i+1]) {
      buf1.emplace_back(i, i+1);
    }
  }

  while (true) {
    for (auto& p : buf1) {
      if ((p.first > 0 && p.second < N1) &&
          (s[p.first-1] == s[p.second+1])) {
        buf2.emplace_back(p.first-1, p.second+1);
      }
    }

    if (buf2.empty()) {
      break;
    }
    buf1.clear();
    buf1.swap(buf2);
  }

  auto& ret = buf1[buf1.size()-1];
  return s.substr(ret.first, ret.second-ret.first+1);
}

void test() {
  cout << longestPalindrome("") << endl;
  cout << longestPalindrome("a") << endl;
  cout << longestPalindrome("aa") << endl;
  cout << longestPalindrome("aaa") << endl;
  cout << longestPalindrome("aaaa") << endl;
  cout << longestPalindrome("babad") << endl;
}
