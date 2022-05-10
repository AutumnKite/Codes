#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<long long> sum(n);
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
    sum[u] += a[v];
    sum[v] += a[u];
  }

  std::vector<std::vector<long long>> f(n, std::vector<long long>(m + 1));
  std::vector<std::vector<long long>> g(n, std::vector<long long>(m + 1));
  long long ans = 0;

  auto dfs = [&](auto &self, int u, int fa) -> void {
    long long v_fa = fa == -1 ? 0 : a[fa];
    long long sum_son = sum[u] - v_fa;
    for (int i = 1; i <= m; ++i) {
      f[u][i] = sum[u];
      g[u][i] = sum_son;
    }
    std::vector<long long> hf(m + 1), hg(m + 1);
    for (int v : E[u]) {
      if (v != fa) {
        self(self, v, u);
        for (int i = 0; i <= m; ++i) {
          ans = std::max(ans, hf[i] + g[v][m - i]);
          ans = std::max(ans, hg[i] + f[v][m - i]);
        }
        for (int i = 1; i <= m; ++i) {
          ans = std::max(ans, f[u][i] + g[v][m - i]);
          ans = std::max(ans, g[u][i] + f[v][m - i] + v_fa - a[v]);
        }
        for (int i = 0; i <= m; ++i) {
          hf[i] = std::max(hf[i], f[v][i]);
          hg[i] = std::max(hg[i], g[v][i]);
        }
        for (int i = 1; i <= m; ++i) {
          f[u][i] = std::max(f[u][i], f[v][i - 1] + sum[u] - a[v]);
          g[u][i] = std::max(g[u][i], g[v][i - 1] + sum_son);
        }
      }
    }
    for (int i = 0; i <= m; ++i) {
      f[u][i] = std::max(f[u][i], hf[i]);
      g[u][i] = std::max(g[u][i], hg[i]);
    }
  };

  dfs(dfs, 0, -1);
  std::cout << ans << "\n";
}
