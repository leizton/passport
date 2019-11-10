#pragma once

#include <exception>
#include <typeinfo>

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>

#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include "pprint.hpp"

using namespace std;

pprint::PrettyPrinter printer(std::cout);

#define print(...) printer.print(__VA_ARGS__)

#define COUT(expr) std::cout << std::boolalpha << (expr) << std::endl;

#define FMTSTR_SIZE 1024
#define FMTSTR\
  char fmtstrtmp[FMTSTR_SIZE]; {va_list ap; va_start(ap, fmt);\
  vsnprintf(fmtstrtmp, FMTSTR_SIZE, fmt, ap); va_end(ap);}

void fmtprint(const char* level, const char* file, const int line,
              const char* func, const char* fmt, ...) {
  FMTSTR;
  std::ostringstream ss;
  // ss << "[" << file << ":" << line << " " << func << "] ";
  ss << level << " " << line << "] ";
  ss << fmtstrtmp;
  std::cout << ss.str() << std::endl;
}

#define PRINT_INFO(fmt, args...)\
  fmtprint("√", __FILE__, __LINE__, __FUNCTION__, fmt, ##args);

#define PRINT_ERROR(fmt, args...)\
  fmtprint("×", __FILE__, __LINE__, __FUNCTION__, fmt, ##args);

#define Eq(actual, expect)\
  if ((actual) == (expect)) { PRINT_INFO("Eq: %s == %s", #actual, #expect); }\
  else { PRINT_ERROR("Eq: %s != %s", #actual, #expect); }
