#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  std::vector<int> col(n, -1);
  int cnt[2] = {};

  auto dfs = [&](auto &self, int u, int c) -> bool {
    if (col[u] != -1) {
      return col[u] == c;
    }
    col[u] = c;
    ++cnt[c];
    for (int v : E[u]) {
      if (!self(self, v, !c)) {
        return false;
      }
    }
    return true;
  };

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (col[i] == -1) {
      cnt[0] = cnt[1] = 0;
      if (!dfs(dfs, i, 0)) {
        std::cout << -1 << "\n";
        return 0;
      }
      ans += std::min(cnt[0], cnt[1]);
    }
  }
  std::cout << ans << "\n";
}
