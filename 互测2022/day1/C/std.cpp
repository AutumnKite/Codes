#include "tree.h"
#include <bits/stdc++.h>

int query(int u, std::vector<int> S) {
  ++u;
  for (int &v : S) {
    ++v;
  }
  return ask(u, S);
}

void add_edge(int u, int v) {
  answer(u + 1, v + 1);
}

void solver(int n, int A, int B) {
  std::mt19937 rnd(time(0));
  std::vector<int> dep(n), fa(n, -1), deg(n), bel(n);
  std::vector<int> Q;
  for (int i = 1; i < n; ++i) {
    dep[i] = query(0, {i});
    if (dep[i] == 1) {
      add_edge(0, i);
      Q.push_back(i);
      fa[i] = 0;
      ++deg[0];
    }
  }
  std::shuffle(Q.begin(), Q.end(), rnd);
  for (int i = 0; i < (int)Q.size(); ++i) {
    int u = Q[i];

    auto solve = [&](auto &self, std::vector<int> S, int q) -> void {
      int sum = 0;
      for (int v : S) {
        sum += dep[v] - dep[u];
      }
      if (sum + 2 * (int)S.size() == q) {
        return;
      }
      if (sum == q) {
        for (int v : S) {
          if (dep[v] == dep[u] + 1) {
            add_edge(u, v);
            Q.push_back(v);
            fa[v] = u;
            ++deg[u];
          }
          bel[v] = u;
        }
        return;
      }
      int mid = S.size() / 2;
      std::vector<int> L(S.begin(), S.begin() + mid);
      std::vector<int> R(S.begin() + mid, S.end());
      int t = query(u, L);
      self(self, L, t);
      self(self, R, q - t);
    };
    
    --deg[fa[u]];
    if (!deg[fa[u]]) {
      for (int v = 0; v < n; ++v) {
        if (bel[v] == fa[u] && dep[v] > dep[u]) {
          if (dep[v] == dep[u] + 1) {
            add_edge(u, v);
            Q.push_back(v);
            fa[v] = u;
            ++deg[u];
          }
          bel[v] = u;
        }
      }
      continue;
    }
    std::vector<int> all;
    for (int v = 0; v < n; ++v) {
      if (bel[v] == fa[u] && dep[v] > dep[u]) {
        all.push_back(v);
      }
    }
    std::shuffle(all.begin(), all.end(), rnd);
    solve(solve, all, query(u, all));
  }
}

#ifdef LOCAL
#include "grader.cpp"
#endif

/*
9 114 514
1 2
2 3
2 4
1 5
4 6
3 7
3 8
2 9
*/