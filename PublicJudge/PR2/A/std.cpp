#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto check = [&](int n, int m, int k) {
    if (k < std::max(n / 2, m / 2)) {
      return false;
    }
    if (k > n * m / 4) {
      return false;
    }
    if (k == n * m / 4 - 1) {
      return false;
    }
    if (n == m && k == n / 2 + 1) {
      return false;
    }
    return true;
  };

  int T;
  std::cin >> T;
  while (T--) {
    int n, m, k;
    std::cin >> n >> m >> k;
    if (n & 1 || m & 1 || (!check(n, m, k))) {
      std::cout << "NO\n";
      continue;
    }
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    int pn = n, pm = m, pk = k;
    int px = 0, py = 0;
    while (pn && pm) {
      if (check(pn - 2, pm - 2, pk - 1)) {
        for (int i = 0; i < pn; ++i) {
          a[px + i][py] = a[px + i][py + pm - 1] = pk;
        }
        for (int i = 0; i < pm; ++i) {
          a[px][py + i] = a[px + pn - 1][py + i] = pk;
        }
        pn -= 2, pm -= 2, pk -= 1;
        ++px, ++py;
      } else if (pn < pm) {
        for (int i = 0; i < pn; i += 2) {
          a[px + i][py] = a[px + i + 1][py] = a[px + i][py + 1] =
              a[px + i + 1][py + 1] = pk;
          --pk;
        }
        pm -= 2, py += 2;
      } else {
        for (int i = 0; i < pm; i += 2) {
          a[px][py + i] = a[px][py + i + 1] = a[px + 1][py + i] =
              a[px + 1][py + i + 1] = pk;
          --pk;
        }
        pn -= 2, px += 2;
      }
    }
    std::cout << "YES\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cout << a[i][j] << " \n"[j == m - 1];
      }
    }
  }
}
