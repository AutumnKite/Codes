#include "guess.h"
#include <bits/stdc++.h>

std::vector<int> solve(int n, int m) {
  std::vector<int> val;
  std::vector<std::tuple<int, int, int, int>> Q;
  for (int i = 0; i < 5; ++i) {
    for (int j = i + 1; j < 5; ++j) {
      for (int k = j + 1; k < 5; ++k) {
        int v = query2(i, j, k);
        Q.emplace_back(i, j, k, v);
        val.push_back(v);
      }
    }
  }
  val.push_back(1);
  val.push_back(n);
  std::sort(val.begin(), val.end());
  val.erase(std::unique(val.begin(), val.end()), val.end());

  auto p = val;
  assert(p.size() == 5);
  do {
    bool ok = true;
    for (auto [i, j, k, v] : Q) {
      ok &= p[i] + p[j] + p[k] ==
            v + std::min({p[i], p[j], p[k]}) + std::max({p[i], p[j], p[k]});
    }
    if (ok) {
      std::vector<int> pos(5);
      for (int i = 0; i < 5; ++i) {
        pos[i] = std::find(p.begin(), p.end(), val[i]) - p.begin();
      }
      break;
    }
  } while (std::next_permutation(p.begin(), p.end()));

  int x0 = std::find(p.begin(), p.end(), val[0]) - p.begin();
  int x1 = std::find(p.begin(), p.end(), val[1]) - p.begin();
  int y0 = std::find(p.begin(), p.end(), val[3]) - p.begin();
  int y1 = std::find(p.begin(), p.end(), val[4]) - p.begin();
  int vx = val[1], vy = val[3];
  std::vector<int> ans(n);
  ans[std::find(p.begin(), p.end(), val[2]) - p.begin()] = val[2];
  for (int i = 5; i < n; ++i) {
    int t = query2(x0, y0, i);
    if (t <= vx) {
      if (t == vx) {
        ans[x0] = vx;
        vx = query2(x0, x1, i);
        x0 = i;
      } else {
        ans[x1] = vx;
        vx = t;
        x1 = i;
      }
    } else if (t >= vy) {
      if (t == vy) {
        ans[y0] = vy;
        vy = query2(y0, y1, i);
        y0 = i;
      } else {
        ans[y1] = vy;
        vy = t;
        y1 = i;
      }
    } else {
      ans[i] = t;
    }
  }
  if (!query1(x0, x1)) {
    std::swap(x0, x1);
  }
  if (query1(y0, y1)) {
    std::swap(y0, y1);
  }
  ans[x0] = 1, ans[x1] = 2;
  ans[y0] = n, ans[y1] = n - 1;
  return ans;
}
