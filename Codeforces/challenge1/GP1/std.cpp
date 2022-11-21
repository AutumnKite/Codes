#include <bits/stdc++.h>

class disjoint_set {
public:
  typedef std::size_t size_type;

protected:
  std::vector<size_type> fa;

public:
  disjoint_set(size_type n = 0) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  size_type find(size_type x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
  }

  bool merge(size_type x, size_type y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    fa[y] = x;
    return true;
  }
};

double now_time() {
  return 1.0 * clock() / CLOCKS_PER_SEC;
}

class tree {
  int n;
  std::vector<std::vector<std::pair<int, int>>> E;

public:
  tree(const std::vector<std::tuple<int, int, int>> &e)
      : n(e.size() + 1), E(n) {
    for (auto [u, v, w] : e) {
      E[u].emplace_back(v, w);
      E[v].emplace_back(u, w);
    }
  }

  std::vector<int> solve(int lim) const {
    int idx = 0;
    std::vector<int> col(n, -1);
    std::vector<int> fa(n, -1), fw(n), size(n, 1);

    auto dfs = [&](auto &self, int u) -> void {
      std::vector<int> son;
      for (auto [v, w] : E[u]) {
        if (v != fa[u]) {
          fa[v] = u;
          fw[v] = w;
          self(self, v);
          size[u] += size[v];
          son.push_back(v);
        }
      }
      std::sort(son.begin(), son.end(), [&](int x, int y) {
        return std::make_pair(size[x], -fw[x]) <
               std::make_pair(size[y], -fw[y]);
      });
      while (size[u] > lim) {
        int v = son.back();
        col[v] = idx++;
        size[u] -= size[v];
        son.pop_back();
      }
    };

    dfs(dfs, 0);
    col[0] = idx++;

    auto color = [&](auto &self, int u) -> void {
      if (col[u] == -1) {
        col[u] = col[fa[u]];
      }
      for (auto [v, w] : E[u]) {
        if (v != fa[u]) {
          self(self, v);
        }
      }
    };

    color(color, 0);
    return col;
  }
};

class graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> E;

public:
  graph(int n, const std::vector<std::tuple<int, int, int>> &e)
      : n(n), m(e.size()), E(n) {
    for (auto [u, v, w] : e) {
      E[u].emplace_back(v, w);
      E[v].emplace_back(u, w);
    }
  }

  std::vector<int> solve() {
    std::vector<std::tuple<int, int, int>> e;
    for (int u = 0; u < n; ++u) {
      for (auto [v, w] : E[u]) {
        if (u < v) {
          e.emplace_back(w, u, v);
        }
      }
    }
    std::sort(e.begin(), e.end());
    disjoint_set D(n);
    std::vector<std::tuple<int, int, int>> ne;
    for (auto [w, u, v] : e) {
      if (D.merge(u, v)) {
        ne.emplace_back(u, v, w);
      }
    }
    tree T(ne);
    double max_score = 0;
    std::vector<int> max_col(n, 0);
    for (int B = 1; B <= 1000 && B <= n && now_time() < 3.9; ++B) {
      auto col = T.solve(B);
      int C = *std::max_element(col.begin(), col.end()) + 1;
      long long sum = 0;
      for (auto [w, u, v] : e) {
        if (col[u] != col[v]) {
          sum += w;
        }
      }
      double score = n - B - C + 1 + 1.0 * sum / 1e9;
      if (score > max_score) {
        max_score = score;
        max_col = std::move(col);
      }
    }
    return max_col;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::tuple<int, int, int>> e;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    e.emplace_back(u, v, w);
  }
  graph G(n, e);
  auto col = G.solve();
  int C = *std::max_element(col.begin(), col.end()) + 1;
  std::vector<std::vector<int>> bel(C);
  for (int i = 0; i < n; ++i) {
    bel[col[i]].push_back(i);
  }
  std::cout << C << "\n";
  for (int i = 0; i < C; ++i) {
    std::cout << bel[i].size();
    for (int u : bel[i]) {
      std::cout << " " << u;
    }
    std::cout << "\n";
  }
}
