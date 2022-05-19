#include <bits/stdc++.h>

class tree {
  int n;
  std::vector<std::vector<int>> E;
  std::vector<int> dep;
  std::vector<bool> occ, lock;
  std::vector<std::pair<int, int>> ans;

  void dfs(int u, int fa) {
    for (int v : E[u]) {
      if (v != fa) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
      }
    }
  }

  void move(int u, int v) {
    std::swap(occ[u], occ[v]);
    ans.emplace_back(u, v);
  }

  bool push(int u, int fa) {
    bool ok = true;
    for (int v : E[u]) {
      if (v != fa && !lock[v]) {
        if (push(v, u) && occ[u]) {
          move(u, v);
        }
        ok &= !occ[v];
      }
    }
    return ok && !occ[u];
  }

  bool pull(int u, int fa) {
    std::vector<int> son;
    for (int v : E[u]) {
      if (v != fa && !lock[v]) {
        if (occ[v]) {
          son.push_back(v);
        }
      }
    }

    if (son.empty()) {
      for (int v : E[u]) {
        if (v != fa && !lock[v]) {
          if (pull(v, u)) {
            move(v, u);
            return true;
          }
        }
      }
      return false;
    }
    int fail = -1;
    for (int v : son) {
      if (fail == -1 && v == son.back()) {
        fail = v;
        break;
      }
      push(v, u);
      if (occ[v]) {
        if (fail == -1) {
          fail = v;
        } else {
          return false;
        }
      }
    }
    move(fail, u);
    return true;
  }

public:
  tree(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  std::pair<std::vector<int>, std::vector<std::pair<int, int>>>
  solve(std::vector<int> S) {
    dep.assign(n, 0);
    dfs(0, -1);
    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin(), id.end(), [&](int x, int y) {
      return dep[x] > dep[y];
    });

    occ.assign(n, false);
    for (int x : S) {
      occ[x] = true;
    }
    lock.assign(n, false);
    ans.clear();
    for (int u : id) {
      if (!occ[u] && !lock[u]) {
        pull(u, -1);
      }
      if (occ[u]) {
        for (int v : E[u]) {
          lock[v] = true;
        }
      }
    }
    S.clear();
    for (int i = 0; i < n; ++i) {
      if (occ[i]) {
        S.push_back(i);
      }
    }
    return std::make_pair(S, ans);
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
    tree G(n);
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      G.add_edge(u, v);
    }

    int k;
    std::cin >> k;
    std::vector<int> A(k), B(k);
    for (int &x : A) {
      std::cin >> x;
      --x;
    }
    for (int &x : B) {
      std::cin >> x;
      --x;
    }
    auto [sA, ansA] = G.solve(A);
    auto [sB, ansB] = G.solve(B);
    if (sA != sB) {
      std::cout << "NO\n";
    } else {
      std::cout << "YES\n";
      std::cout << ansA.size() + ansB.size() << "\n";
      for (auto [x, y] : ansA) {
        std::cout << x + 1 << " " << y + 1 << "\n";
      }
      std::reverse(ansB.begin(), ansB.end());
      for (auto [x, y] : ansB) {
        std::cout << y + 1 << " " << x + 1 << "\n";
      }
    }
  }
}
