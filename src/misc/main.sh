#!/bin/sh
g++ -std=c++20 -DLOCAL -O0 -g0 -x c++-header main.hpp -o main.hpp.gch
g++ -std=c++20 -DLOCAL -O0 -g0 -o ./case/main.out main.cpp -ftime-report

for in in ./case/*.in; do
  echo "------------------------------------"
  ans="${in%.in}.ans"
  echo "cerr: "
  ./case/main.out < "$in" > "$ans"
  echo
  echo "$ans:"
  cat $ans
  echo "------------------------------------"
done