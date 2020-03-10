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

#include "pprint.hpp"

using namespace std;

pprint::PrettyPrinter printer(cout);

#define pprint(...) printer.print(__VA_ARGS__)

#define COUT(expr) cout << boolalpha << (expr) << endl;

#define ASSERT_EQ(expect, actual) {\
  auto actual_v = actual;\
  assertEquals(__LINE__, expect, actual_v);\
}

void assertEquals(int lineno, int expect, int actual) {
  if (expect == actual) return;
  ostringstream ss;
  ss << lineno << "] assertEquals fail.";
  ss << " expect=" << expect << ", actual=" << actual << "\n";
  cout << ss.str();
}


void printss(ostringstream& ss) {
  ss << "\n";
  cout << ss.str();
}

template<class T>
void print(vector<T> v) {
  ostringstream out;
  out << "[";
  bool first = true;
  for (T& e : v) {
    if (!first) out << ",";
    first = false;
    out << e;
  }
  out << "]";
  printss(out);
}

void print(int v) {
  ostringstream out;
  out << v;
  printss(out);
}

void print(bool v) {
  ostringstream out;
  out << boolalpha << v;
  printss(out);
}

template<class T>
ostream& operator <<(ostream& out, const vector<T>& v) {
  out << "[";
  bool first = true;
  for (T& e : v) {
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
