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

pprint::PrettyPrinter printer(std::cout);

#define pprint(...) printer.print(__VA_ARGS__)

#define COUT(expr) std::cout << std::boolalpha << (expr) << std::endl;

void fmtprint(const char* level, const char* file, const int line,
              const char* func, const char* fmt, ...) {
  const int bufsize = 1024;
  char fmtstrtmp[bufsize];
  {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(fmtstrtmp, bufsize, fmt, ap);
    va_end(ap);
  }

  std::ostringstream ss;
  ss << level << " " << line << "]  ";
  ss << fmtstrtmp;
  std::cout << ss.str() << std::endl;
}

#define PRINT_INFO(fmt, args...)\
  // fmtprint("√", __FILE__, __LINE__, __FUNCTION__, fmt, ##args);

#define PRINT_ERROR(fmt, args...)\
  fmtprint("×", __FILE__, __LINE__, __FUNCTION__, fmt, ##args);

#define Eq(actual, expect)\
  if ((actual) == (expect)) { PRINT_INFO("Eq: %s == %s", #actual, #expect); }\
  else { PRINT_ERROR("Eq: %s != %s", #actual, #expect); }


template<class T>
void print(std::vector<T> v) {
  std::ostringstream out;
  out << "[";
  bool first = true;
  for (T& e : v) {
    if (!first) out << ",";
    first = false;
    out << e;
  }
  out << "]\n";
  std::cout << out.str();
}
