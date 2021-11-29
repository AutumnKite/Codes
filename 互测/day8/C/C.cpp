#include <bits/stdc++.h>

bool query(int);
void modify(int, bool);

bool WereYouLast(int n, int m) {
  if (n == 1024) {
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

  int x = 0;
  for (int i = 0; i < 5; ++i) {
    x |= query(i + 1) << i;
  }
  if ((1 << x) == n) {
    return true;
  }
  int now = query(x + 6);
  modify(x + 6, !now);
  if (now || 1 << x == n / 2) {
    ++x;
  } else {
    x = 0;
  }
  for (int i = 0; i < 5; ++i) {
    modify(i + 1, x >> i & 1);
  }
  return false;
}
