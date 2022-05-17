#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m, lim;
    std::cin >> n >> m >> lim;
    std::string a, b;
    std::cin >> a >> b;

    if (std::abs(n - m) > lim) {
      std::cout << "NO\n";
      continue;
    }

    std::vector<std::vector<int>> f(lim + 1, std::vector<int>(2 * lim + 1, -1));
    std::vector<std::vector<int>> g(lim + 1, std::vector<int>(2 * lim + 1));
    
    auto upd = [&](int i, int j, int v, int d) {
      j += lim;
      if (v > f[i][j]) {
        f[i][j] = v;
        g[i][j] = d;
      }
    };

    f[0][lim] = 0;
    for (int i = 0; i <= lim; ++i) {
      for (int j = -i; j <= i; ++j) {
        int &p = f[i][j + lim];
        if (p != -1) {
          int q = p + j;
          while (p < n && q < m && a[p] == b[q]) {
            ++p, ++q;
          }
          if (i < lim) {
            if (p < n) {
              upd(i + 1, j - 1, p + 1, 1);
            }
            if (q < m) {
              upd(i + 1, j + 1, p, -1);
            }
            if (p < n && q < m) {
              upd(i + 1, j, p + 1, 0);
            }
          }
        }
      }
    }

    int k = 0, now = m - n;
    while (k <= lim && f[k][now + lim] < n) {
      ++k;
    }
    if (k == lim + 1) {
      std::cout << "NO\n";
      continue;
    }
    std::cout << "YES\n";
    std::cout << k << "\n";
    while (k) {
      int d = g[k][now + lim];
      --k, now += d;
      int p = f[k][now + lim], q = p + now;
      if (d == -1) {
        std::cout << "INSERT " << p + 1 << " " << b[q] << "\n";
      } else if (d == 1) {
        std::cout << "DELETE " << p + 1 << "\n";
      } else {
        std::cout << "REPLACE " << p + 1 << " " << b[q] << "\n";
      }
    }
  }
}
