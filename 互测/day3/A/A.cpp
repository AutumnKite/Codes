#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, lim;
  std::cin >> n >> lim;
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  std::vector<int> a(n);
  for (int &x : a) {
    std::cin >> x;
  }

  std::vector<std::vector<int>> d(n + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      d[j].push_back(i);
    }
  }

  std::vector<std::vector<std::pair<int, int>>> pf(n + 1);
  for (int i = 1; i <= n; ++i) {
    int x = i;
    for (int p : d[i]) {
      if (p > 1 && x % p == 0) {
        int c = 0;
        while (x % p == 0) {
          x /= p;
          ++c;
        }
        pf[i].emplace_back(p, c);
      }
    }
  }

  std::vector<std::vector<int>> pw(n + 1, std::vector<int>(lim + 1));

  for (int i = 1; i <= n; ++i) {
    pw[i][0] = 1;
    for (int j = 0; j < lim; ++j) {
      if (pw[i][j] <= n / i) {
        pw[i][j + 1] = pw[i][j] * i;
      } else {
        pw[i][j + 1] = n + 1;
      }
    }
  }

  std::vector<int> fa(n, -1), size(n), son(n);

  auto init = [&](auto &self, int u) -> void {
    size[u] = 1;
    son[u] = -1;
    for (int v : E[u]) {
      if (v != fa[u]) {
        fa[v] = u;
        self(self, v);
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]]) {
          son[u] = v;
        }
      }
    }
  };

  init(init, 0);

  std::vector<long long> ans(n);

  std::vector<int> sum(n + 1);
  std::vector<int> sta;

  auto clear = [&]() {
    for (int x : sta) {
      for (int y : d[x]) {
        sum[y] = 0;
      }
    }
    sta.clear();
  };

  auto insert = [&](int x, long long &s) {
    int sgn = 1;
    for (auto [p, c] : pf[x]) {
      if (c > lim) {
        return;
      }
      if (c & 1) {
        sgn = -sgn;
      }
    }
    sta.push_back(x);
    for (int y : d[x]) {
      sum[y] += sgn;
    }
    for (int S = 0; S < (1 << (int)pf[x].size()); ++S) {
      int pro = 1;
      int cnt = 0;
      for (int i = 0; i < (int)pf[x].size(); ++i) {
        if (S >> i & 1) {
          ++cnt;
          auto [p, c] = pf[x][i];
          int v = pw[p][lim - c + 1];
          if (pro <= n / v) {
            pro *= v;
          } else {
            pro = n + 1;
          }
        }
      }
      if (pro <= n) {
        if (cnt & 1) {
          s -= sum[pro] * sgn;
        } else {
          s += sum[pro] * sgn;
        }
      }
    }
  };

  auto add = [&](auto &self, int u, long long &s) -> void {
    insert(a[u], s);
    for (int v : E[u]) {
      if (v != fa[u]) {
        self(self, v, s);
      }
    }
  };

  auto dfs = [&](auto &self, int u) -> void {
    clear();
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        self(self, v);
      }
    }
    if (son[u] != -1) {
      self(self, son[u]);
      ans[u] = ans[son[u]];
    }
    insert(a[u], ans[u]);
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        add(add, v, ans[u]);
      }
    }
  };

  dfs(dfs, 0);

  for (int i = 0; i < n; ++i) {
    std::cout << ans[i] << "\n";
  }
}
