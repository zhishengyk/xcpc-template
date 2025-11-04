#!/bin/sh
set -e
g++ -std=c++20 -O0 -g0 -o test.out test.cpp
g++ -std=c++20 -O0 -g0 -o main.out main.cpp
g++ -std=c++20 -O0 -g0 -o true.out true.cpp
g++ -std=c++20 -O0 -g0 -o checker.out checker.cpp

d="temp"; n="${1:-0}"; i=0

while :; do
  i=$((i+1))
  in="$d/$i.in"
  out="$d/$i.out"
  ans="$d/$i.ans"
  ./test.out > "$in"
  ./main.out < "$in" > "$out"
  ./true.out < "$in" > "$ans"
  res1=$(cat "$in" "$out" | ./checker.out | tail -n1 || true)
  res2=$(cat "$in" "$ans" | ./checker.out | tail -n1 || true)
  if [ "$res1" != "$res2" ]; then
    echo "Test $i WA!"; echo ""
    echo "$in:";  cat "$in";  echo ""
    echo "$out:"; cat "$out"; echo ""
    echo "$ans:"; cat "$ans"; echo ""
    exit 1
  fi
  echo "Test $i Correct!"
  if [ "$i" -ge "$n" ]; then
    exit 0
  fi
done