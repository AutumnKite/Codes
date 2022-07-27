#include <bits/stdc++.h>

using i64 = int64_t;

constexpr i64 INF = std::numeric_limits<i64>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<i64, i64>> a, b;
    for (int i = 0; i < n; ++i) {
      i64 x, y, w;
      std::cin >> x >> y >> w;
      a.emplace_back(x + y, w);
      b.emplace_back(x - y, w);
    }
    std::vector<std::pair<i64, int>> Qa, Qb;
    for (int i = 0; i < q; ++i) {
      i64 x, y;
      std::cin >> x >> y;
      Qa.emplace_back(x + y, i);
      Qb.emplace_back(x - y, i);
    }
    std::vector<i64> ans(q);

    auto solve = [&](std::vector<std::pair<i64, i64>> p,
                     std::vector<std::pair<i64, int>> Q) {
      std::sort(Q.begin(), Q.end());
      std::vector<i64> s1(q, -INF), s0(q, -INF);
      for (int i = 0; i < n; ++i) {
        i64 t = p[i].first + p[i].second;
        auto it = std::lower_bound(Q.begin(), Q.end(), std::make_pair(t, 0));
        if (it != Q.begin()) {
          int k = it - Q.begin() - 1;
          s1[k] = std::max(s1[k], -p[i].first);
        }
        if (it != Q.end()) {
          int k = it - Q.begin();
          s0[k] = std::max(s0[k], p[i].second);
        }
      }
      for (int i = q - 2; i >= 0; --i) {
        s1[i] = std::max(s1[i], s1[i + 1]);
      }
      for (int i = 1; i < q; ++i) {
        s0[i] = std::max(s0[i], s0[i - 1]);
      }
      for (int i = 0; i < q; ++i) {
        ans[Q[i].second] = std::max(ans[Q[i].second],
                                    std::max(s1[i] + Q[i].first, s0[i]));
      }
    };

    solve(a, Qa);
    solve(b, Qb);
    for (int i = 0; i < n; ++i) {
      a[i].first = -a[i].first;
      b[i].first = -b[i].first;
    }
    for (int i = 0; i < q; ++i) {
      Qa[i].first = -Qa[i].first;
      Qb[i].first = -Qb[i].first;
    }
    solve(a, Qa);
    solve(b, Qb);
    for (int i = 0; i < q; ++i) {
      std::cout << ans[i] << "\n";
    }
  }
}
