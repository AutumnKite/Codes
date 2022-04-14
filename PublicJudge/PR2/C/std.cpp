#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m;
    long long L, R;
    std::cin >> n >> m >> L >> R;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    std::vector<std::vector<int>> E(n);
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      E[u].push_back(v);
      E[v].push_back(u);
    }

    std::vector<std::vector<std::vector<long long>>> f(
        n, std::vector<std::vector<long long>>(m + 1));

    auto dfs = [&](auto &self, int u, int fa) -> void {
      f[u][0].push_back(a[u]);
      for (auto v : E[u]) {
        if (v != fa) {
          self(self, v, u);
          std::vector<std::vector<long long>> g(m + 1);
          for (int i = 0; i <= m; ++i) {
            for (int j = 0; i + j <= m; ++j) {
              for (auto wi : f[u][i]) {
                for (auto wj : f[v][j]) {
                  if (wi + wj <= R) {
                    g[i + j].push_back(wi + wj);
                  }
                }
              }
            }
          }
          for (int i = 0; i <= m; ++i) {
            std::sort(g[i].begin(), g[i].end());
            f[u][i].clear();
            for (auto w : g[i]) {
              while (f[u][i].size() > 1 && w - *++f[u][i].rbegin() <= R - L) {
                f[u][i].pop_back();
              }
              f[u][i].push_back(w);
            }
          }
        }
      }
      for (int i = m - 1; i >= 0; --i) {
        for (auto w : f[u][i]) {
          if (L <= w && w <= R) {
            f[u][i + 1].push_back(0);
            break;
          }
        }
      }
    };

    dfs(dfs, 0, -1);
    for (int i = 0; i <= m; ++i) {
      bool ok = false;
      for (auto w : f[0][i]) {
        if (L <= w && w <= R) {
          ok = true;
          break;
        }
      }
      std::cout << (ok ? 1 : 0);
    }
    std::cout << "\n";
  }
}
