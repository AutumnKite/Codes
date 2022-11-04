#!/bin/bash
count=0
while true; do
  ./gen > data.in
  ./std < data.in > std.out
  ./bf < data.in > bf.out
  count=`expr $count + 1`
  if diff std.out bf.out -b; then
    printf "test $count: "
    printf "AC\n"
  else
    printf "test $count: "
    printf "WA\n"
    exit 0
  fi
done
