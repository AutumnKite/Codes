#include "guess.h"

#include <bits/stdc++.h>

void init(int subtask_id, int T) {}

long long solve(long long P, int n) {
  int k = 0;
  __uint128_t v = 0, pw = 1;
  while (true) {
    int x = query(0) ^ 2;
    if (P % n == 1) {
      x = (n - x) % n;
    }
    bool ok = pw >= P;
    ++k;
    pw *= n;
    v = v * n + x;
    if (ok) {
      break;
    }
  }

  long long seed = (P * v + pw - 1) / pw;

  auto gen = [&]() {
    seed = 1ll * seed * n % P;
    return seed % n;
  };

  for (int i = 0; i < k; ++i) {
    gen();
  }

  long long l = 1, r = 1e18;
  while (l < r) {
    long long mid = (l + r) >> 1;
    int v = query(mid) ^ gen();
    if (v == 1) {
      return mid;
    } else if (v == 2) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

#ifdef LOCAL
#include "grader.cpp"
#endif
