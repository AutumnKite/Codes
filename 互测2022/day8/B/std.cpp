#include "tmp.h"
#include <bits/stdc++.h>

int n, p;

void init(int N, bool Type, int P) {
  n = N, p = P;
}

bool guess(unsigned long long A, int x) {
  if (x != -1) {
    return __builtin_parityll(A) ^ (x & 1);
  }
  return A >> (n / 3 - 1) & 1;
}
