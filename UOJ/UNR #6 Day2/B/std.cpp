#include "tree.h"

#include <bits/stdc++.h>

using components = std::vector<std::vector<int>>;

components merge(const components &A, const std::vector<int> &B) {
  std::vector<std::pair<long long, int>> all;
  for (const auto &p : A) {
    for (int x : p) {
      all.emplace_back(1ll * p[0] << 32 | B[x], x);
    }
  }
  std::sort(all.begin(), all.end());
  components res;
  long long lst = -1;
  for (const auto &p : all) {
    if (p.first == lst) {
      res.back().push_back(p.second);
    } else {
      lst = p.first;
      if (!res.empty() && res.back().size() == 1) {
        res.pop_back();
      }
      res.emplace_back(1, p.second);
    }
  }
  if (!res.empty() && res.back().size() == 1) {
    res.pop_back();
  }
  return res;
}

std::vector<std::pair<int, int>> solve(int n) {
  int lg = 0;
  while ((1 << lg) < n - 1) {
    ++lg;
  }
  std::vector<std::array<std::vector<int>, 2>> Q(lg);
  for (int i = 0; i < lg; ++i) {
    for (int j = 0; j < 2; ++j) {
      std::vector<int> vec(n - 1);
      for (int k = 0; k < n - 1; ++k) {
        vec[k] = (k >> i & 1) == j;
      }
      auto res = query(vec);
      Q[i][j].resize(n);
      for (const auto &p : res) {
        for (int x : p) {
          Q[i][j][x] = p[0];
        }
      }
    }
  }

  std::vector<std::pair<int, int>> edge;

  auto work = [&](auto &self, int k, const components &C) -> void {
    if (k == 0) {
      if (!C.empty()) {
        edge.emplace_back(C[0][0], C[0][1]);
      }
      return;
    }
    --k;
    self(self, k, merge(C, Q[k][0]));
    self(self, k, merge(C, Q[k][1]));
  };

  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  work(work, lg, components(1, id));
  return edge;
}

#ifdef LOCAL
#include "grader.cpp"
#endif
