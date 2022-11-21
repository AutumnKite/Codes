#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, seed;
  std::cin >> n >> seed;
  std::vector<std::vector<int>> a(n, std::vector<int>(n + 1));
  if (seed) {
    std::mt19937 rnd(seed);
    for (int i = 0; i < n; ++i) {
      std::vector<int> p(n + 1);
      for (int j = 0; j <= n; ++j) {
        p[j] = j;
        std::swap(p[j], p[rnd() % (j + 1)]);
      }
      for (int j = 0; j <= n; ++j) {
        a[i][p[j]] = j;
      }
    }
  } else {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= n; ++j) {
        int x;
        std::cin >> x;
        --x;
        a[i][x] = j;
      }
    }
  }
  std::vector<int> pos(n);
  for (int k = 0; k < n; ++k) {
    std::vector<bool> vis(n + 1);
    for (int i = 1; i <= n; ++i) {
      int x = (k - i + n) % n;
      if (i == 1) {
        pos[x] = 0;
      }
      while (vis[a[x][pos[x]]]) {
        ++pos[x];
      }
      vis[a[x][pos[x]]] = true;
    }
    int ans = std::find(vis.begin(), vis.end(), false) - vis.begin();
    std::cout << ans + 1 << " \n"[k == n - 1];
  }
}
