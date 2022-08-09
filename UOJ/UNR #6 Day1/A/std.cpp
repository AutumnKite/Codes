#include <bits/stdc++.h>

constexpr long long INF = std::numeric_limits<long long>::max() / 10;

class graph {
  int n;
  std::vector<std::vector<std::pair<int, int>>> E;

  void work(std::vector<long long> &dis) {
    std::priority_queue<std::pair<long long, int>> Q;
    std::vector<bool> vis(n);
    for (int i = 0; i < n; ++i) {
      if (dis[i] < INF) {
        Q.emplace(-dis[i], i);
      }
    }
    while (!Q.empty()) {
      int u = Q.top().second;
      Q.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto p : E[u]) {
        int v = p.first, w = p.second;
        if (dis[u] + w < dis[v]) {
          dis[v] = dis[u] + w;
          Q.emplace(-dis[v], v);
        }
      }
    }
  }

public:
  graph(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v, int w) {
    E[u].emplace_back(v, w);
    E[v].emplace_back(u, w);
  }

  long long solve(std::vector<int> nd) {
    int k = nd.size();
    std::vector<std::vector<long long>> dis(k, std::vector<long long>(n, INF));
    for (int i = 0; i < k; ++i) {
      dis[i][nd[i]] = 0;
      work(dis[i]);
      for (int u = 0; u < n; ++u) {
        assert(dis[i][u] < INF);
      }
    }
    long long ans = INF;
    for (int u = 0; u < n; ++u) {
      long long max = 0;
      for (int i = 0; i < k; ++i) {
        max = std::max(max, dis[i][u]);
      }
      ans = std::min(ans, 2 * max);
      for (auto p : E[u]) {
        int v = p.first, w = p.second;
        std::vector<std::pair<long long, long long>> t;
        for (int i = 0; i < k; ++i) {
          long long A = dis[i][u], B = dis[i][v] + w;
          t.emplace_back(B - A, 2 * A);
        }
        std::sort(t.begin(), t.end());
        std::vector<long long> pre(k + 1), suf(k + 1);
        pre[0] = -INF;
        for (int i = 0; i < k; ++i) {
          pre[i + 1] = std::max(pre[i], 2 * t[i].first + t[i].second);
        }
        suf[k] = -INF;
        for (int i = k - 1; i >= 0; --i) {
          suf[i] = std::max(suf[i + 1], t[i].second);
        }
        for (int i = 0; i <= k; ++i) {
          long long l = i > 0 ? t[i - 1].first : 0;
          long long r = i < k ? t[i].first : 2 * w;
          long long x = (pre[i] - suf[i]) / 2;
          x = std::max(x, l);
          x = std::min(x, r);
          ans = std::min(ans, std::max(pre[i] - x, suf[i] + x));
        }
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
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    G.add_edge(u, v, w);
  }
  int k;
  std::cin >> k;
  std::vector<int> p(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> p[i];
    --p[i];
  }
  p.push_back(0);
  std::cout << G.solve(p) << "\n";
}
