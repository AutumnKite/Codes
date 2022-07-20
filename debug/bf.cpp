#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  std::vector<std::vector<int>> Ea(n), Eb(m);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    Ea[u].push_back(v);
    Ea[v].push_back(u);
  }
  for (int i = 0; i < m - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    Eb[u].push_back(v);
    Eb[v].push_back(u);
  }

  auto dfs = [&](auto &self, auto &E, int u, int fa, auto &id) -> void {
    if (fa != -1) {
      E[u].erase(std::find(E[u].begin(), E[u].end(), fa));
    }
    id.push_back(u);
    for (int v : E[u]) {
      self(self, E, v, u, id);
    }
  };

  std::vector<int> ida, idb;
  dfs(dfs, Ea, 0, -1, ida);
  dfs(dfs, Eb, 0, -1, idb);
  std::reverse(ida.begin(), ida.end());
  std::reverse(idb.begin(), idb.end());

  std::vector<std::vector<int>> f(n, std::vector<int>(m));
  for (int x : ida) {
    for (int y : idb) {
      for (int yv : Eb[y]) {
        f[x][y] = std::max(f[x][y], f[x][yv]);
      }
      for (int xv : Ea[x]) {
        f[x][y] = std::max(f[x][y], f[xv][y]);
      }
      if (a[x] == b[y]) {
        auto func = [&](int i, int j) {
          if (i < (int)Ea[x].size() && j < (int)Eb[y].size()) {
            return f[Ea[x][i]][Eb[y][j]];
          } else {
            return 0;
          }
        };
        int c = std::max(Ea[x].size(), Eb[y].size());
        std::vector<int> id(c);
        std::iota(id.begin(), id.end(), 0);
        do {
          int sum = 1;
          for (int i = 0; i < c; ++i) {
            sum += func(i, id[i]);
          }
          f[x][y] = std::max(f[x][y], sum);
        } while (std::next_permutation(id.begin(), id.end()));
      }
    }
  }
  std::cout << f[0][0] << "\n";
}
