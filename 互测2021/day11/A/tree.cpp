#include <bits/stdc++.h>
#include "tree.h"

std::vector<int> solve(int n) {
  std::vector<int> fa(n, -1);
  std::vector<int> w(n, -1);

  auto get_sum = [&](std::vector<bool> vis) {
    std::vector<int> q;
    for (int i = 0; i < n; ++i) {
      if (vis[i]) {
        q.push_back(i + 1);
      }
    }
    return query(q);
  };

  auto get_son = [&](auto &self, int u, int l, int r,
                     int now, std::vector<int> &res) -> void {
    std::vector<bool> vis(n, true);
    for (int x = u; x != -1; x = fa[x]) {
      vis[x] = false;
    }
    int cnt = 0;
    for (int i = l; i < r; ++i) {
      if (fa[i] == -1) {
        ++cnt;
        vis[i] = false;
      }
    }
    if (!cnt) {
      return;
    }
    int tmp = get_sum(vis);
    if (tmp == now) {
      return;
    }
    if (l + 1 == r) {
      res.push_back(l);
      fa[l] = u;
      w[l] = tmp;
      return;
    }
    int mid = (l + r) >> 1;
    self(self, u, l, mid, now, res);
    self(self, u, mid, r, now, res);
  };

  std::vector<bool> vis(n, true);
  vis[0] = false;
  w[0] = get_sum(vis);
  std::vector<int> Q(1, 0);
  for (int i = 0; i < (int)Q.size(); ++i) {
    int u = Q[i];
    std::vector<int> son;
    get_son(get_son, u, 1, n, w[u], son);
    for (int v : son) {
      Q.push_back(v);
    }
  }

  std::vector<int> res(n - 1);
  for (int i = 1; i < n; ++i) {
    res[i - 1] = fa[i] + 1;
  }
  return res;
}
