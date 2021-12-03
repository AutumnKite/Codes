#include <bits/stdc++.h>
#include "integer.h"

std::mt19937 rnd(time(0));

std::vector<int> findPermutation(int n) {
  std::vector<int> res(n, -1);
  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  std::shuffle(id.begin(), id.end(), rnd);
  int lst = 0;
  for (int i = 0; i < n; ++i) {
    lst = operate(i);
  }
  for (int k = 0, cnt = 0; cnt < n; ++k) {
    std::vector<int> tmp;
    int t = n + std::__lg((k + 1) & -(k + 1));
    for (int i : id) {
      if (res[i] == -1) {
        int now = operate(i);
        int x = lst - now + 1;
        if (x > 0) {
          t -= x;
          res[i] = t;
          ++cnt;
        }
        lst = now;
      } else if (res[i] >= k) {
        tmp.push_back(i);
      }
    }
    for (int x : tmp) {
      lst = operate(x);
    }
  }
  return res;
}
