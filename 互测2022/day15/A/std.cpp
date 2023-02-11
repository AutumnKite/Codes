#include <bits/stdc++.h>

constexpr int INF = std::numeric_limits<int>::max() / 2;

void update(int &a, int b) {
  a = std::min(a, b);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<int> p(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> p[i];
    --p[i];
  }
  std::vector<std::vector<std::tuple<int, int, int>>> E(n);
  for (int i = 0; i < m; ++i) {
    int u, v, a, b;
    std::cin >> u >> v >> a >> b;
    --u, --v;
    E[v].emplace_back(u, a, b);
  }

  auto work = [&](std::vector<int> &dis) {
    std::priority_queue<std::pair<int, int>> Q;
    for (int i = 0; i < n; ++i) {
      if (dis[i] < INF) {
        Q.emplace(-dis[i], i);
      }
    }
    std::vector<bool> vis(n);
    while (!Q.empty()) {
      int u = Q.top().second;
      Q.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto [v, a, b] : E[u]) {
        if (dis[v] > dis[u] + a) {
          dis[v] = dis[u] + a;
          Q.emplace(-dis[v], v);
        }
      }
    }
  };

  std::vector f(1 << k, std::vector(m + 1, std::vector(n, INF)));
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j <= m; ++j) {
      f[1 << i][j][p[i]] = 0;
    }
  }
  for (int S = 1; S < (1 << k); ++S) {
    for (int u = 0; u < n; ++u) {
      for (int T = (S - 1) & S; T; T = (T - 1) & S) {
        for (int i = 0, j = 0; i <= m; ++i) {
          while (j <= m && f[S ^ T][j][u] > f[T][i][u]) {
            ++j;
          }
          if (i + j <= m) {
            update(f[S][i + j][u], f[T][i][u]);
          }
        }
      }
      for (int i = 0; i < m; ++i) {
        update(f[S][i + 1][u], f[S][i][u]);
      }
    }
    for (int i = 0; i <= m; ++i) {
      work(f[S][i]);
      if (i == m) {
        break;
      }
      for (int u = 0; u < n; ++u) {
        for (auto [v, a, b] : E[u]) {
          update(f[S][i + 1][v], f[S][i][u] + b);
        }
      }
    }
  }
  for (int i = 0; i <= m; ++i) {
    std::cout << f[(1 << k) - 1][i][0] << " \n"[i == m];
  }
}
