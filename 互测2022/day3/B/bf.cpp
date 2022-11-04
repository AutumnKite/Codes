#include <bits/stdc++.h>

class tree {
  int n;
  std::vector<std::vector<int>> E;

public:
  tree(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  int query(int u, int v, int d) {
    std::vector<int> fa(n, -1);

    auto dfs = [&](auto &self, int u) -> void {
      for (int v : E[u]) {
        if (v != fa[u]) {
          fa[v] = u;
          self(self, v);
        }
      }
    };

    dfs(dfs, u);
    std::vector<int> dis(n, d + 1);
    std::vector<int> Q;
    for (int x = v; x != -1; x = fa[x]) {
      dis[x] = 0;
      Q.push_back(x);
    }
    for (int i = 0; i < (int)Q.size(); ++i) {
      int u = Q[i];
      for (int v : E[u]) {
        if (dis[u] + 1 < dis[v]) {
          dis[v] = dis[u] + 1;
          Q.push_back(v);
        }
      }
    }
    return Q.size();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  tree T(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    T.add_edge(u, v);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int u, v, d;
    std::cin >> u >> v >> d;
    --u, --v;
    std::cout << T.query(u, v, d) << "\n";
  }
}
