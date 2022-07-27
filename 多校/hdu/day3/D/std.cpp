#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    std::vector<long long> sum(1 << n), sum2(1 << n);
    for (int i = 0; i < n; ++i) {
      sum[1 << i] = a[i];
    }
    for (int S = 1; S < (1 << n); ++S) {
      sum[S] = sum[S & -S] + sum[S & (S - 1)];
    }
    for (int S = 1; S < (1 << n); ++S) {
      sum2[S] = sum[S] * sum[S];
    }
    std::cout << std::accumulate(sum2.begin(), sum2.end(), 0ll) % 998244353
              << "\n";
    if (m == 1) {
      continue;
    }
    std::vector<long long> f(sum2);
    for (int S = 1; S < (1 << n); ++S) {
      int cnt = __builtin_popcount(S);
      if (cnt <= 6) {
        int l = 1 << std::__lg(S);
        for (int T = S; T >= l; T = (T - 1) & S) {
          f[S] = std::min(f[S], sum2[S ^ T] + sum2[T]);
        }
        continue;
      }
      int T0 = 0, T1 = 0;
      int mid = cnt / 2;
      int idx = 0;
      for (int i = 0; i < n; ++i) {
        if (S >> i & 1) {
          if (idx < mid) {
            T0 |= 1 << i;
          } else {
            T1 |= 1 << i;
          }
          ++idx;
        }
      }
      std::vector<long long> all;
      all.reserve(1 << mid);
      for (int T = T0; ; T = (T - 1) & T0) {
        all.push_back(sum[T]);
        if (T == 0) {
          break;
        }
      }
      std::sort(all.begin(), all.end());
      long long max = 0;
      for (int T = T1; ; T = (T - 1) & T1) {
        auto p = std::upper_bound(all.begin(), all.end(), sum[S] / 2 - sum[T]);
        if (p != all.begin()) {
          max = std::max(max, sum[T] + *(--p));
        }
        if (T == 0) {
          break;
        }
      }
      f[S] = max * max + (sum[S] - max) * (sum[S] - max);
    }
    std::cout << std::accumulate(f.begin(), f.end(), 0ll) % 998244353 << "\n";
    for (int k = 3; k <= m; ++k) {
      std::vector<long long> g(f);
      for (int S = 1; S < (1 << n); ++S) {
        int l = 1 << std::__lg(S);
        for (int T = S; T >= l; T = (T - 1) & S) {
          g[S] = std::min(g[S], f[S ^ T] + sum2[T]);
        }
      }
      std::cout << std::accumulate(g.begin(), g.end(), 0ll) % 998244353 << "\n";
      f.swap(g);
    }
  }
}
/*
50
20 3
1 2 3 5 1 1 2 5 9 1 3 5 8 9 2 3 8 9 6 1
20 3
1 2 3 5 1 1 2 5 9 1 3 5 8 9 2 3 8 9 6 1
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
12 11
1 2 5 2 3 6 5 7 8 2 3 8
*/
