#include <bits/stdc++.h>

bool query(int);
void modify(int, bool);

bool WereYouLast(int n, int m) {
  int p = 9;
  while (p >= 0 && query(p + 1)) {
    modify(p + 1, false);
    --p;
  }
  if (p == -1) {
    return true;
  } else {
    modify(p + 1, true);
    return false;
  }
}
