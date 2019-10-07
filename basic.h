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
