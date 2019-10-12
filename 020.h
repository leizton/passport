#include "basic.h"

/*

# 有效的括号

输入只包含 ( ) [ ] { } 这6种字符

# ex
() => true
()[] => true
(] => false

*/

bool isValid(string s) {
  // 或者用数组
  static map<char, char> match = {
    {')','('}, {']','['}, {'}','{'}
  };
  stack<char> sk;

  for (char x : s) {
    char y = match[x];
    if (y == 0) {
      sk.push(x);
    } else {
      if (sk.empty() || y != sk.top())
        return false;
      sk.pop();
    }
  }
  return sk.empty();
}

void test() {
  print(isValid("("));  // F
  print(isValid("]"));  // F
  print(isValid("()"));  // T
  print(isValid("(){}"));  // T
  print(isValid("(]"));  // F
  print(isValid("(([]))"));  // T
  print(isValid("([(]))"));  // F
}
