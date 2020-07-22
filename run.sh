#!/bin/bash
rm -f a.out

CPP_FLAGS='g++ -std=c++17'

function init_include_flags(){
  INCLUDE_FLAGS="$INCLUDE_FLAGS -I$1"
  for e in `ls $1`; do  
    t=$1"/"$e
    if [ -d $t ]; then
      init_include_flags $t
    fi  
  done
}
INCLUDE_FLAGS=''
init_include_flags .

CPP="$CPP_FLAGS $INCLUDE_FLAGS"

if [ $# -gt 0 ]; then
  target=`find . -name "$1*.h" | awk -F '/' '{print $3}'`
  $CPP main.cc -DSOLU_HEADER="\"$target\""
else
  $CPP main.cc
fi

if [ -f a.out ]; then
  ./a.out
fi
