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

class graph {
  int n;
  std::vector<std::pair<int, int>> edge;
  std::vector<std::vector<std::pair<int, int>>> E;

  std::vector<bool> vis;
  std::vector<int> sta;
  std::vector<bool> in;

  std::vector<int> cyc;

  bool dfs(int u, int fid) {
    vis[u] = true;
    in[u] = true;
    sta.push_back(u);
    for (auto [v, id] : E[u]) {
      if (fid != id) {
        if (!vis[v]) {
          if (dfs(v, id)) {
            return true;
          }
        } else {
          int x;
          do {
            x = sta.back();
            cyc.push_back(x);
            in[x] = false;
            sta.pop_back();
          } while (x != v);
          return true;
        }
      }
    }
    return false;
  }

public:
  graph(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].emplace_back(v, edge.size());
    E[v].emplace_back(u, edge.size());
    edge.emplace_back(u, v);
  }

  bool check() {
    int rt = 0;
    while (rt < n && E[rt].empty()) {
      ++rt;
    }
    disjoint_set D(n);
    int cnt = 0;
    for (auto [u, v] : edge) {
      cnt += !D.merge(u, v);
    }
    if (cnt != 1) {
      return false;
    }
    for (int i = 0; i < n; ++i) {
      if (!E[i].empty() && D.find(i) != D.find(rt)) {
        return false;
      }
    }
    vis.assign(n, false);
    in.assign(n, false);
    sta.clear();
    cyc.clear();
    if (!dfs(rt, -1)) {
      return false;
    }
    std::vector<bool> on(n);
    for (int x : cyc) {
      on[x] = true;
    }
    for (int i = 0; i < n; ++i) {
      if (!on[i] && (int)E[i].size() > 2) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> edge(n);
  for (auto &[u, v] : edge) {
    std::cin >> u >> v;
    --u, --v;
  }

  std::vector<std::vector<bool>> ok(n, std::vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      graph G(n);
      for (int k = i; k <= j; ++k) {
        G.add_edge(edge[k].first, edge[k].second);
      }
      ok[i][j] = G.check();
    }
  }

  int q;
  std::cin >> q;
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    --l;
    int ans = 0;
    for (int i = l; i < r; ++i) {
      for (int j = i; j < r; ++j) {
        ans += ok[i][j];
      }
    }
    std::cout << ans << "\n";
  }
}
