#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int T;
  std::cin >> T;
  while (T--) {
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
    std::vector<int> size(n), sum(n), cnt(n + 1);
    
    auto dfs = [&](auto &self, int u, int fa) -> void {
      size[u] = 1;
      sum[u] = (E[u].size() == 1 && fa != -1);
      for (int v : E[u]) {
        if (v != fa) {
          self(self, v, u);
          size[u] += size[v];
          sum[u] += sum[v];
        }
      }
      cnt[size[u]] += sum[u];
    };

    dfs(dfs, 0, -1);
    std::vector<int> ans;
    for (int i = 1; i <= n; ++i) {
      if (cnt[i] == sum[0]) {
        ans.push_back(i);
      }
    }
    std::cout << ans.size() << "\n";
    std::string sep = "";
    for (int x : ans) {
      std::cout << sep << x;
      sep = " ";
    }
    std::cout << "\n";
  }
}
