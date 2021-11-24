#include <bits/stdc++.h>

class graph {
  int n, m;
  std::vector<std::vector<std::tuple<int, int, bool>>> E;

  std::vector<int> hd;
  std::vector<bool> vis;

  void dfs(int u) {

  }

public:
  graph(int t_n = 0) : n(t_n), m(0), E(n) {}

  void add_edge(int u, int v) {
    E[u].emplace_back(v, m, false);
    E[v].emplace_back(u, m, true);
    ++m;
  }

  std::vector<std::pair<int, bool>> cycle() {
    hd.assign(n, 0);
    vis.assign(m, 0);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
}
