#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

class graph {
  int n;
  std::vector<std::vector<int>> E;
  std::vector<int> mat;
  std::vector<bool> vis;

  bool dfs(int u) {
    std::shuffle(E[u].begin(), E[u].end(), rnd);
    vis[u] = true;
    for (int v : E[u]) {
      if (mat[v] != -1 && vis[mat[v]]) {
        continue;
      }
      int t = mat[v];
      mat[u] = v, mat[v] = u;
      if (t == -1) {
        return true;
      }
      mat[t] = -1;
      if (dfs(t)) {
        return true;
      }
      mat[u] = -1, mat[v] = t, mat[t] = v;
    }
    return false;
  }

public:
  graph(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  std::vector<int> match(int T = 3) {
    mat.assign(n, -1);
    while (T--) {
      for (int i = 0; i < n; ++i) {
        if (mat[i] == -1) {
          vis.assign(n, false);
          dfs(i);
        }
      }
    }
    return mat;
  }
};

class sat {
  int n;
  std::vector<std::vector<int>> E;

  int idx;
  std::vector<int> dfn, low;
  std::vector<bool> vis;
  std::vector<int> sta;
  int cnt;
  std::vector<int> col;

  void tarjan(int u) {
    dfn[u] = low[u] = idx++;
    sta.push_back(u);
    vis[u] = true;
    for (int v : E[u]) {
      if (dfn[v] == -1) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
      } else if (vis[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
    if (dfn[u] == low[u]) {
      int x;
      do {
        x = sta.back();
        sta.pop_back();
        vis[x] = false;
        col[x] = cnt;
      } while (x != u);
      ++cnt;
    }
  }

public:
  sat(int t_n) : n(t_n), E(n * 2) {}

  void add_edge(int u, int su, int v, int sv) {
    E[u << 1 | su].push_back(v << 1 | sv);
    E[v << 1 | !sv].push_back(u << 1 | !su);
  }

  bool solve(std::vector<bool> &res) {
    idx = 0;
    dfn.assign(n * 2, -1);
    low.assign(n * 2, -1);
    sta.clear();
    vis.assign(n * 2, false);
    cnt = 0;
    col.assign(n * 2, -1);
    for (int i = 0; i < n * 2; ++i) {
      if (dfn[i] == -1) {
        tarjan(i);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (col[i << 1] == col[i << 1 | 1]) {
        return false;
      }
    }
    res.assign(n, false);
    for (int i = 0; i < n; ++i) {
      res[i] = col[i << 1] > col[i << 1 | 1];
    }
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n, m;
  std::cin >> n >> m;
  graph G(n);
  std::vector<std::pair<int, int>> edge;
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    G.add_edge(u, v);
    edge.emplace_back(u, v);
  }
  auto mat = G.match();

  std::vector<std::pair<int, int>> id(n, std::make_pair(-1, -1));
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (mat[i] != -1 && id[i].first == -1) {
      id[i] = std::make_pair(cnt, 0);
      id[mat[i]] = std::make_pair(cnt, 1);
      ++cnt;
    }
  }

  sat S(cnt);
  for (auto [u, v] : edge) {
    if (mat[u] != -1 && mat[v] != -1) {
      S.add_edge(id[u].first, !id[u].second, id[v].first, id[v].second);
    } else if (mat[u] != -1) {
      S.add_edge(id[u].first, !id[u].second, id[u].first, id[u].second);
    } else if (mat[v] != -1) {
      S.add_edge(id[v].first, !id[v].second, id[v].first, id[v].second);
    } else {
      assert(false);
    }
  }
  
  std::vector<bool> res;
  if (S.solve(res)) {
    std::cout << cnt << "\n";
    for (int i = 0; i < n; ++i) {
      if (mat[i] != -1 && res[id[i].first] == id[i].second) {
        std::cout << i + 1 << " ";
      }
    }
    std::cout << "\n";
    return 0;
  }

  for (int x = 0; x < n; ++x) {
    if (1.0 * clock() / CLOCKS_PER_SEC > 0.9) {
      break;
    }
    sat S(cnt);
    for (auto [u, v] : edge) {
      if (x == u || x == v) {
        continue;
      }
      if (mat[u] != -1 && mat[v] != -1) {
        S.add_edge(id[u].first, !id[u].second, id[v].first, id[v].second);
      } else if (mat[u] != -1) {
        S.add_edge(id[u].first, !id[u].second, id[u].first, id[u].second);
      } else if (mat[v] != -1) {
        S.add_edge(id[v].first, !id[v].second, id[v].first, id[v].second);
      } else {
        assert(false);
      }
    }

    std::vector<bool> res;
    if (S.solve(res)) {
      std::cout << cnt + 1 << "\n";
      for (int i = 0; i < n; ++i) {
        if (x == i || (mat[i] != -1 && res[id[i].first] == id[i].second)) {
          std::cout << i + 1 << " ";
        }
      }
      std::cout << "\n";
      return 0;
    }
  }
  std::cout << "not smol\n";
}
