#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  std::vector<std::pair<int, int>> ans;

  auto dfs = [&](auto &self, int u, int fa) -> int {
    std::vector<int> son;
    for (int v : E[u]) {
      if (v != fa) {
        int p = self(self, v, u);
        if (p != -1) {
          ans.emplace_back(u, p);
        } else {
          son.push_back(v);
        }
      }
    }
    for (int i = 0; i + 1 < (int)son.size(); i += 2) {
      ans.emplace_back(son[i], son[i + 1]);
    }
    return son.size() & 1 ? son.back() : -1;
  };

  dfs(dfs, 0, -1);
  std::cout << ans.size() << "\n";
  for (auto [u, v] : ans) {
    std::cout << u + 1 << " " << v + 1 << "\n";
  }
}
