#include <bits/stdc++.h>

class graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> E;

  int idx;
  std::vector<int> dfn, low;
  std::vector<int> sta;
  int cnt;
  std::vector<int> col;

  void tarjan(int u, int fi) {
    dfn[u] = low[u] = idx++;
    sta.push_back(u);
    for (auto p : E[u]) {
      int v = p.first, id = p.second;
      if (id != fi) {
        if (dfn[v] == -1) {
          tarjan(v, id);
          low[u] = std::min(low[u], low[v]);
        } else {
          low[u] = std::min(low[u], dfn[v]);
        }
      }
    }
    if (dfn[u] == low[u]) {
      int x;
      do {
        x = sta.back();
        sta.pop_back();
        col[x] = cnt;
      } while (x != u);
      ++cnt;
    }
  }

public:
  graph(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].emplace_back(v, m);
    E[v].emplace_back(u, m);
    ++m;
  }

  int solve() {
    idx = 0;
    dfn.assign(n, -1);
    low.assign(n, -1);
    col.assign(n, -1);
    sta.clear();
    cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        tarjan(i, -1);
      }
    }
    std::vector<std::vector<int>> G(cnt);
    for (int u = 0; u < n; ++u) {
      for (auto p : E[u]) {
        int v = p.first;
        if (col[u] != col[v]) {
          G[col[u]].push_back(col[v]);
        }
      }
    }
    std::vector<bool> vis(cnt);

    auto dfs = [&](auto &self, int u, int fa) -> std::pair<int, int> {
      vis[u] = true;
      std::pair<int, int> res(0, u);
      for (int v : G[u]) {
        if (v != fa) {
          auto tmp = self(self, v, u);
          ++tmp.first;
          res = std::max(res, tmp);
        }
      }
      return res;
    };

    int ans = -1;
    for (int i = 0; i < cnt; ++i) {
      if (!vis[i]) {
        ans += dfs(dfs, dfs(dfs, i, -1).second, -1).first + 1;
      }
    }
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  graph G(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    G.add_edge(u, v);
  }
  std::cout << G.solve() << "\n";
}
