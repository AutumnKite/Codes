#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    --n;
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
      b[i] = a[i + 1] - a[i];
    }

    int lg = 30 + std::__lg(n);
    std::vector<std::vector<int>> f(n + 1, std::vector<int>(lg + 1, -1));
    for (int i = n - 1; i >= 0; --i) {
      if (!b[i]) {
        f[i][0] = i + 1 < n && !b[i + 1] ? f[i + 1][0] : i + 1;
        continue;
      }
      int k = 0;
      while (b[i] % 2 == 0) {
        ++k;
        b[i] /= 2;
      }
      f[i][k] = i + 1;
    }
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j < lg; ++j) {
        if (f[i][j] != -1 && f[f[i][j]][j] != -1 && b[i] == b[f[i][j]]) {
          f[i][j + 1] = f[f[i][j]][j];
        }
      }
    }
    std::vector<int> g(n + 1, n);
    g[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j <= lg; ++j) {
        if (f[i][j] != -1) {
          g[i] = std::min(g[i], g[f[i][j]] + 1);
        }
      }
    }
    std::cout << g[0] + 1 << "\n";
  }
}
