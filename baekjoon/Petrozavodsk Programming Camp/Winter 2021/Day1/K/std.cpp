#include <bits/stdc++.h>

constexpr int INF = std::numeric_limits<int>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> E(n + m);
    for (int i = 0; i < m; ++i) {
      int r;
      std::cin >> r;
      for (int j = 0; j < r; ++j) {
        int x;
        std::cin >> x;
        --x;
        E[x].push_back(n + i);
        E[n + i].push_back(x);
      }
    }

    int q;
    std::cin >> q;
    std::vector<bool> del(m);
    std::vector<int> s(q);
    for (int i = 0; i < q; ++i) {
      std::cin >> s[i];
      --s[i];
      del[s[i]] = true;
    }
    std::reverse(s.begin(), s.end());

    auto bfs = [&](int st) {
      std::vector<int> Q;
      std::vector<int> dis(n + m, INF);
      dis[st] = 0;
      Q.push_back(st);
      for (int i = 0; i < (int)Q.size(); ++i) {
        int u = Q[i];
        for (int v : E[u]) {
          if (v >= n && del[v - n]) {
            continue;
          }
          if (dis[v] == INF) {
            dis[v] = dis[u] + 1;
            Q.push_back(v);
          }
        }
      }
      dis.resize(n);
      return dis;
    };

    int max = 0;
    std::vector<std::vector<int>> min(n, std::vector<int>(n, INF));

    auto update = [&](int x) {
      auto dis = bfs(n + x);
      max = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
          min[i][j] = std::min(min[i][j], dis[i] + dis[j]);
          if (min[i][j] < INF) {
            max = std::max(max, min[i][j]);
          }
        }
      }
    };

    for (int i = 0; i < m; ++i) {
      if (!del[i]) {
        update(i);
      }
    }
    std::vector<int> ans;
    ans.push_back(max);
    for (int x : s) {
      del[x] = false;
      update(x);
      ans.push_back(max);
    }
    std::reverse(ans.begin(), ans.end());
    
    for (int x : ans) {
      std::cout << x / 2 - 1 << "\n";
    }
  }
}