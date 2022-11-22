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

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

class forest {
  int n;
  std::vector<std::vector<std::pair<int, int>>> E;

public:
  forest(int n, const std::vector<std::tuple<int, int, int>> &e)
      : n(n), E(n) {
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

    for (int i = 0; i < n; ++i) {
      if (fa[i] == -1) {
        dfs(dfs, i);
        col[i] = idx++;
        color(color, i);
      }
    }
    return col;
  }
};

class graph {
  int n, m;
  std::vector<std::vector<std::tuple<int, int, int>>> E;

  std::vector<int> S;
  std::vector<std::vector<long long>> dis;

public:
  graph(int n, const std::vector<std::tuple<int, int, int>> &e)
      : n(n), m(e.size()), E(n) {
    int idx = 0;
    for (auto [u, v, w] : e) {
      E[u].emplace_back(v, w, idx);
      E[v].emplace_back(u, w, idx);
      ++idx;
    }
  }

  std::vector<int> solve0(double TL) const {
    std::vector<std::tuple<int, int, int>> e;
    for (int u = 0; u < n; ++u) {
      for (auto [v, w, id] : E[u]) {
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
    forest T(n, ne);
    double max_score = 0;
    std::vector<int> max_col(n, 0);
    for (int B = 1; B <= 2000 && B <= n && now_time() < TL - 0.2; ++B) {
      auto col = T.solve(B);
      int C = *std::max_element(col.begin(), col.end()) + 1;
      long long sum = 0;
      for (auto [w, u, v] : e) {
        if (col[u] != col[v]) {
          sum += w;
        }
      }
      double score = n - B - C + 1 + 1.0 * sum / 1e8;
      if (score > max_score) {
        max_score = score;
        max_col = std::move(col);
      }
    }
    return max_col;
  }

  std::vector<int> solve1() const {
    int idx = 0;
    std::vector<int> dfn(n, -1), low(n);
    std::vector<std::tuple<int, int, int>> ne;

    auto tarjan = [&](auto &self, int u, int fa) -> void {
      dfn[u] = low[u] = idx++;
      for (auto [v, w, id] : E[u]) {
        if (v != fa) {
          if (dfn[v] == -1) {
            self(self, v, u);
            low[u] = std::min(low[u], low[v]);
            if (low[v] > dfn[u]) {
              ne.emplace_back(u, v, w);
            }
          } else {
            low[u] = std::min(low[u], dfn[v]);
          }
        }
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        tarjan(tarjan, i, -1);
      }
    }
    forest T(n, ne);
    return T.solve(1000);
  }

  double final_score(const std::vector<int> &nS, const std::vector<int> &col,
                     double k, double TL) {
    if (S != nS) {
      S = nS;
      dis.assign(S.size(), std::vector<long long>(n, INF));
      for (int i = 0; i < (int)S.size(); ++i) {
        int s = S[i];
        std::priority_queue<std::pair<long long, int>> Q;
        std::vector<bool> vis(n);
        Q.emplace(0, s);
        dis[i][s] = 0;
        while (!Q.empty()) {
          int u = Q.top().second;
          Q.pop();
          if (vis[u]) {
            continue;
          }
          vis[u] = true;
          for (auto [v, w, id] : E[u]) {
            if (dis[i][u] + w < dis[i][v]) {
              dis[i][v] = dis[i][u] + w;
              Q.emplace(-dis[i][v], v);
            }
          }
        }
      }
    }
    double max = 0;
    for (int i = 0; i < (int)S.size() && now_time() < TL - 0.2; ++i) {
      int s = S[i];
      std::vector<int> pre(n, -1);
      std::vector<long long> dis0(n, INF), cost(n, INF);
      std::priority_queue<std::tuple<long long, int, int>> Q;
      std::vector<bool> vis(n);
      Q.emplace(0, 1, s);
      dis0[s] = cost[s] = 0;
      while (!Q.empty()) {
        int u = std::get<2>(Q.top());
        Q.pop();
        if (vis[u]) {
          continue;
        }
        if (u != s) {
          max = std::max(max, 1.0 * (cost[u] - dis[i][u]) / dis[i][u]);
        }
        vis[u] = true;
        for (auto [v, w, id] : E[u]) {
          long long tw = dis0[u] + w;
          if (col[u] == col[v]) {
            tw -= w;
            id = pre[u];
          }
          if (std::make_pair(tw, id) < std::make_pair(dis0[v], pre[v])) {
            dis0[v] = tw;
            pre[v] = id;
            cost[v] = cost[u] + w;
            Q.emplace(-dis0[v], -pre[v], v);
          }
        }
      }
    }
    int C = *std::max_element(col.begin(), col.end()) + 1;
    std::vector<int> cnt(C);
    for (int c : col) {
      ++cnt[c];
    }
    int B = *std::max_element(cnt.begin(), cnt.end()) + 1;
    return std::max(0.0, n - C - B + 1 - k * max);
  }
};

void print(std::vector<int> col) {
  int C = *std::max_element(col.begin(), col.end()) + 1;
  std::vector<std::vector<int>> bel(C);
  for (int i = 0; i < (int)col.size(); ++i) {
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
  int L;
  double k;
  std::cin >> L >> k;
  std::vector<int> S(L);
  for (int &x : S) {
    std::cin >> x;
  }

  graph G(n, e);
  auto col0 = G.solve0(4.0);
  auto ans0 = G.final_score(S, col0, k, 4.4);
  auto col1 = G.solve1();
  auto ans1 = G.final_score(S, col1, k, 5.0);
  if (ans0 > ans1) {
    print(col0);
    std::cerr << ans0 << "\n";
  } else {
    print(col1);
    std::cerr << ans1 << "\n";
  }

  std::cerr << now_time() << "\n";
}
