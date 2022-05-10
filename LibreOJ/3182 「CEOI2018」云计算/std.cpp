#include <bits/stdc++.h>

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<std::tuple<int, int, int, int>> a;
  int n;
  std::cin >> n;
  int lim = 0;
  for (int i = 0; i < n; ++i) {
    int c, f, v;
    std::cin >> c >> f >> v;
    lim += c;
    a.emplace_back(-f, 0, c, v);
  }
  int m;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int c, f, v;
    std::cin >> c >> f >> v;
    a.emplace_back(-f, 1, c, v);
  }
  std::sort(a.begin(), a.end());

  std::vector<long long> f(lim + 1, -INF);
  f[0] = 0;
  for (auto [w, tp, c, v] : a) {
    if (tp == 0) {
      for (int i = lim; i >= c; --i) {
        f[i] = std::max(f[i], f[i - c] - v);
      }
    } else {
      for (int i = 0; i <= lim - c; ++i) {
        f[i] = std::max(f[i], f[i + c] + v);
      }
    }
  }
  std::cout << *std::max_element(f.begin(), f.end()) << "\n";
}
