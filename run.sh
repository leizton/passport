#!/bin/bash
rm -f a.out
g++ -std=c++17 main.cc

if [ -f a.out ]; then
  ./a.out
fi
