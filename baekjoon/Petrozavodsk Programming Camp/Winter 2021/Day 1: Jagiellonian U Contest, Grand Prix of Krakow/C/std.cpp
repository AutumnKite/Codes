#include <bits/stdc++.h>

class graph {
  int n;
  std::vector<std::vector<int>> E;

  std::vector<bool> vis;
  std::vector<int> sta;
  std::vector<int> cyc;

  bool find_cycle(int u, int fa) {
    sta.push_back(u);
    vis[u] = true;
    for (int v : E[u]) {
      if (v != fa) {
        if (!vis[v]) {
          if (find_cycle(v, u)) {
            return true;
          }
        } else {
          int t;
          do {
            t = sta.back();
            sta.pop_back();
            cyc.push_back(t);
          } while (t != v);
          return true;
        }
      }
    }
    vis[u] = false;
    sta.pop_back();
    return false;
  }

  int count(int u, int fa) {
    int res = 0;
    for (int v : E[u]) {
      if (v != fa && !vis[v]) {
        res += count(v, u);
      }
    }
    return std::max(res, 1);
  }

public:
  graph(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  int solve() {
    sta.clear();
    cyc.clear();
    vis.assign(n, false);
    find_cycle(0, -1);
    vis.assign(n, false);
    for (int x : cyc) {
      vis[x] = true;
    }
    int sum = 0;
    bool ex = false, ex2 = false;
    bool lst = E[cyc.back()].size() == 2;
    for (int x : cyc) {
      if (E[x].size() > 2) {
        sum += count(x, -1);
        lst = false;
      } else {
        ex = true;
        ex2 |= lst;
        lst = true;
      }
    }
    if (ex2) {
      return sum + 2;
    } else if (ex) {
      return sum + 1;
    } else {
      return sum;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    graph G(n);
    for (int i = 0; i < n; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      G.add_edge(u, v);
    }
    std::cout << std::max(3, G.solve()) << "\n";
  }
}
