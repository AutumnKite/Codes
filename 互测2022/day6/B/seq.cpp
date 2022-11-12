#include <bits/stdc++.h>
#include "seq.h"

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

void SEQ(int n, int M) {
  std::mt19937 rnd(time(0));
  answer(1);
  std::vector<int> cnt(n * 2, -1);
  disjoint_set D(n + 1);
  std::vector<std::vector<int>> E(n + 1);
  int c = n;
  for (int k = 1; c > 1; ++k) {
    long long s = (1ll << k) + 1;
    std::vector<std::pair<int, int>> edge;
    for (int p = 3; p <= s && p < 2 * n; p += 2) {
      if (s % p == 0) {
        cnt[p] = k;
        for (int i = std::max(1, p - n); i <= n && i < p; i += 2) {
          int j = p - i;
          edge.emplace_back(i, j);
        }
      }
    }
    std::shuffle(edge.begin(), edge.end(), rnd);
    for (auto [i, j] : edge) {
      if (D.merge(i, j)) {
        E[i].push_back(j);
        E[j].push_back(i);
        --c;
      }
    }
  }
  std::vector<int> now(n + 1), goal(n + 1);
  for (int i = 1; i <= n; ++i) {
    goal[Get(i)] = i;
    now[i] = i;
  }
  std::vector<int> Q;
  std::vector<int> deg(n + 1);
  for (int i = 1; i <= n; ++i) {
    deg[i] = E[i].size();
    if (deg[i] == 1) {
      Q.push_back(i);
    }
  }
  for (int i = 0; i < (int)Q.size(); ++i) {
    int u = Q[i];

    std::vector<int> fa(n + 1);

    auto dfs = [&](auto &self, int u) -> void {
      for (int v : E[u]) {
        if (v != fa[u]) {
          fa[v] = u;
          self(self, v);
        }
      }
    };

    dfs(dfs, u);

    int x = std::find(now.begin(), now.end(), goal[u]) - now.begin();
    while (x != u) {
      int y = fa[x];
      int t = x;
      for (int i = 0; i < cnt[x + y]; ++i) {
        if (t % 2 == 0) {
          add(now[x], now[y]);
          t /= 2;
        } else {
          add(now[y], now[x]);
          t = x + y - (x + y - t) / 2;
        }
      }
      std::swap(now[x], now[y]);
      x = y;
    }
    for (int v : E[u]) {
      --deg[v];
      if (deg[v] == 1) {
        Q.push_back(v);
      }
    }
  }
}

#ifdef LOCAL
#include "grader.cpp"
#endif
