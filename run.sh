#!/bin/bash
rm -f a.out

CPP_FLAGS='g++ -std=c++17'

CPP="$CPP_FLAGS -I ."

if [ $# -gt 0 ]; then
  target=`find . -name "$1*.h"`
  $CPP main.cc -DSOLU_HEADER="\"$target\""
else
  $CPP main.cc
fi

if [ -f a.out ]; then
  ./a.out
fi
