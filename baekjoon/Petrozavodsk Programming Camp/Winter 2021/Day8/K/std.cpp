#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int m = *std::max_element(a.begin(), a.end());

  std::vector f(n + 1, std::vector(n + 1, std::vector<int>(m + 1, n * m)));
  for (int i = 0; i <= n; ++i) {
    f[i][i][0] = 0;
  }
  for (int l = n - 1; l >= 0; --l) {
    for (int r = l + 1; r <= n; ++r) {
      for (int k = 0; k <= m; ++k) {
        for (int i = l + 1; i < r; ++i) {
          for (int j = 0; j <= k; ++j) {
            f[l][r][k] = std::min(f[l][r][k], f[l][i][j] + f[i][r][k - j]);
          }
        }
        for (int j = 0; j <= m; ++j) {
          if (k + j >= a[r - 1]) {
            int v = (k + j) / 2;
            f[l][r][v] = std::min(f[l][r][v], f[l][r - 1][k] + j);
          }
        }
      }
      for (int k = m - 1; k >= 0; --k) {
        f[l][r][k] = std::min(f[l][r][k], f[l][r][k + 1]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    std::cout << f[0][i][0] << " \n"[i == n];
  }
}
