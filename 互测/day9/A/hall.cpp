#include <bits/stdc++.h>
#include "hall.h"

class init_half {
  short n;
  std::vector<short> bit;
  std::vector<short> cnt;
  std::vector<std::vector<short>> rk;

public:
  init_half(short t_n)
  : n(t_n), bit(1 << n), cnt(n + 1), 
    rk(n + 1, std::vector<short>(1 << n, -1)) {
    for (short S = 1; S < (1 << n); ++S) {
      bit[S] = bit[S >> 1] + (S & 1);
    }
    for (short S = 0; S < (1 << n); ++S) {
      rk[bit[S]][S] = cnt[bit[S]]++;
    }
  }

  short count(short k) const {
    if (k < 0 || k > n) {
      return 0;
    } else {
      return cnt[k];
    }
  }

  short popcount(short S) const {
    return bit[S];
  }

  short rank(short S) const {
    return rk[bit[S]][S];
  }
};

class init {
  int n, k;
  int B1, B2;
  init_half f1, f2;
  std::vector<int> pre;

public:
  init(int t_n, int t_k)
  : n(t_n), k(t_k), B1(n / 2), B2(n - n / 2), f1(B1), f2(B2), pre(B1 + 2) {
    for (int i = 0; i <= B1; ++i) {
      pre[i + 1] = pre[i] + f1.count(i) * f2.count(k - i);
    }
  }

  int count() const {
    return pre[B1 + 1];
  }

  int rank(int S) const {
    int t = f1.popcount(S >> B2);
    return pre[t] + f1.rank(S >> B2) * f2.count(k - t)
                  + f2.rank(S & ((1 << B2) - 1));
  }
};

int solve(int n, int K, int s) {
  static init f(n, K - 1);
  static std::vector<bool> vis(f.count());

  for (int i = 0; i < n; ++i) {
    if (s >> i & 1) {
      int x = f.rank(s ^ (1 << i));
      if (!vis[x]) {
        vis[x] = true;
        return s ^ (1 << i);
      }
    }
  }

  return 0;
}
