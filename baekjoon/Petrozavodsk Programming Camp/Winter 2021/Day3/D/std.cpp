#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> E(n + 1);
  std::vector<int> fa(n + 1, -1);
  std::vector<int> c(n + 1), r(n + 1);
  std::cin >> c[0];
  for (int i = 1; i <= n; ++i) {
    std::cin >> fa[i] >> c[i] >> r[i];
    E[fa[i]].push_back(i);
  }

  int ans = 2e9;

  auto dfs = [&](auto &self, int u, int need) -> void {
    need = std::max(need, c[u]) - r[u];
    ans = std::min(ans, need);
    for (int v : E[u]) {
      self(self, v, need);
    }
  };

  dfs(dfs, 0, 0);
  std::cout << ans << "\n";
}
