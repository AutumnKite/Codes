#include <bits/stdc++.h>

const int INF = std::numeric_limits<int>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<int> f(n), g(n);
  f[0] = INF, g[0] = -INF;
  for (int i = 1; i < n; ++i) {
    f[i] = -INF, g[i] = INF;
    if (a[i] <= a[i - 1]) {
      g[i] = std::min(g[i], g[i - 1]);
    }
    if (a[i] >= a[i - 1]) {
      f[i] = std::max(f[i], f[i - 1]);
    }
    if (a[i] <= f[i - 1]) {
      g[i] = std::min(g[i], a[i - 1]);
    }
    if (a[i] >= g[i - 1]) {
      f[i] = std::max(f[i], a[i - 1]);
    }
  }
  if (f[n - 1] > -INF || g[n - 1] < INF) {
    std::cout << "yes\n";
  } else {
    std::cout << "no\n";
  }
}
