#include <bits/stdc++.h>

constexpr int INF = std::numeric_limits<int>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> a(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> a[i][j];
    }
  }

  int sum = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (a[i][j] != -1) {
        int t = std::min(a[i][j], a[j][i]);
        a[i][j] -= t;
        a[j][i] -= t;
        sum += t;
      }
    }
  }

  std::vector<int> f(1 << n, INF);
  std::vector<std::vector<std::vector<int>>>
      g(1 << n, std::vector<std::vector<int>>(n, std::vector<int>(n, INF))),
      h(g);
  
  auto upd = [&](int &a, int b) {
    a = std::min(a, b);
  };

  for (int i = 0; i < n; ++i) {
    f[1 << i] = 0;
  }
  for (int S = 1; S < (1 << n); ++S) {
    for (int i = 0; i < n; ++i) {
      if (S >> i & 1) {
        for (int j = 0; j < n; ++j) {
          if (S >> j & 1 && a[j][i] != -1) {
            upd(f[S], h[S][i][j] + a[j][i]);
          }
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      if (S >> i & 1) {
        for (int j = 0; j < n; ++j) {
          if (S >> j & 1) {
            for (int k = 0; k < n; ++k) {
              if (a[j][k] != -1 && !(S >> k & 1)) {
                upd(g[S | (1 << k)][i][k], f[S] + a[j][k]);
                upd(h[S | (1 << k)][i][k], g[S][i][j] + a[j][k]);
                upd(h[S | (1 << k)][i][k], h[S][i][j] + a[j][k]);
              }
            }
          }
        }
      }
    }
  }
  int ans = f[(1 << n) - 1];
  if (ans == INF) {
    std::cout << -1 << "\n";
  } else {
    std::cout << sum + ans << "\n";
  }
}
