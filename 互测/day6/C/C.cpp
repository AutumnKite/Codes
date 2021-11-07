#include <bits/stdc++.h>

constexpr long long INF = std::numeric_limits<long long>::max();

void upd(long long &a, long long b) {
  a = std::min(a, b);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<long long> t(n + 1), x(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> t[i] >> x[i];
  }

  std::vector<long long> v(x);
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());

  std::vector<int> p(n + 1);
  for (int i = 0; i <= n; ++i) {
    p[i] = std::lower_bound(v.begin(), v.end(), x[i]) - v.begin();
  }

  std::vector<long long> g(n + 1, INF);
  std::vector<std::vector<bool>> f(n + 1, std::vector<bool>(v.size()));
  g[0] = 0;
  for (int i = 0; i < n; ++i) {
    if (t[i] + std::abs(x[i] - x[i + 1]) <= t[i + 1]) {
      for (int j = 0; j < (int)v.size(); ++j) {
        if (f[i][j]) {
          f[i + 1][j] = true;
        }
      }
    }
    if (g[i] <= t[i]) {
      int k = i + 1;
      while (k <= n && x[k] == x[i]) {
        ++k;
      }
      if (k > n) {
        std::cout << "YES\n";
        return 0;
      }
      upd(g[k], std::max(g[i] + std::abs(x[i] - x[k]), t[k - 1]));
      if (std::max(g[i] + std::abs(x[i] - x[k]), t[k - 1]) <= t[k]) {
        f[k][p[i]] = true;
      }
      for (int j = 0; j < (int)v.size(); ++j) {
        if (std::max(g[i] + std::abs(v[j] - x[i]), t[k - 1])
            + std::abs(v[j] - x[k]) <= t[k]) {
          f[k][j] = true;
        }
      }
    }
    if (f[i][p[i + 1]]) {
      int k = i + 2;
      while (k <= n && x[k] == x[i + 1]) {
        ++k;
      }
      if (k > n) {
        std::cout << "YES\n";
        return 0;
      }
      upd(g[k], std::max(t[i] + std::abs(x[i] - x[k]), t[k - 1]));
      if (std::max(t[i] + std::abs(x[i] - x[k]), t[k - 1]) <= t[k]) {
        f[k][p[i + 1]] = true;
      }
      for (int j = 0; j < (int)v.size(); ++j) {
        if (std::max(t[i] + std::abs(v[j] - x[i]), t[k - 1])
            + abs(v[j] - x[k]) <= t[k]) {
          f[k][j] = true;
        }
      }
    }
  }
  if (g[n] <= t[n]) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}
