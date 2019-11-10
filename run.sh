#!/bin/bash
rm -f a.out

if [ $# -gt 0 ]; then
  g++ -std=c++17 main.cc -DSOLU_HEADER="\"$1.h\""
else
  g++ -std=c++17 main.cc
fi

if [ -f a.out ]; then
  ./a.out
fi
