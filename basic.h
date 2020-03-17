#pragma once

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <exception>
#include <typeinfo>

#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <type_traits>
#include <typeinfo>
#include <ctime>

#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>

using namespace std;

#define assert_eq(expect, actual) {\
  auto actual_v = actual;\
  _assert_eq(__LINE__, expect, actual_v);\
}

template<class T, class U>
void _assert_eq(int lineno, T expect, U actual) {
  ostringstream ss;
  ss << "[" << lineno << "] assert_eq";
  if (expect == actual) {
    ss << " ok";
  } else {
    ss << " fail.";
    ss << " expect=" << expect << ", actual=" << actual;
  }
  ss << "\n";
  cout << ss.str();
}

#define assert_T(expr) if (expr) {} else {\
  ostringstream ss;\
  ss << "[" << __LINE__ << "] assert_T fail\n";\
  cout << ss.str();\
}

#define assert_F(expr) if (expr) {\
  ostringstream ss;\
  ss << "[" << __LINE__ << "] assert_F fail\n";\
  cout << ss.str();\
}

#define COUT(expr) cout << boolalpha << (expr) << endl;

template<class T>
ostream& operator <<(ostream& out, const vector<T>& v) {
  out << "[";
  bool first = true;
  for (const T& e : v) {
    if (!first) out << ",";
    first = false;
    out << e;
  }
  out << "]";
  return out;
}

template<class K, class V>
ostream& operator <<(ostream& out, const map<K,V>& m) {
  out << "[";
  bool first = true;
  for (auto& p : m) {
    if (!first) out << ",";
    first = false;
    out << p.first << "=" << p.second;
  }
  out << "]";
  return out;
}

template<class K, class V>
ostream& operator <<(ostream& out, const unordered_map<K,V>& m) {
  out << "[";
  bool first = true;
  for (auto& p : m) {
    if (!first) out << ",";
    first = false;
    out << p.first << "=" << p.second;
  }
  out << "]";
  return out;
}

template<class T>
void printvec(vector<T> v) {
  ostringstream ss;
  ss << v << "\n";
  cout << ss.str();
}

template<class K, class V>
void printmap(map<K,V> m) {
  ostringstream ss;
  ss << m << "\n";
  cout << ss.str();
}

template<class K, class V>
void printunmap(unordered_map<K,V> m) {
  ostringstream ss;
  ss << m << "\n";
  cout << ss.str();
}
