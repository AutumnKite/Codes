#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(3);

  int T;
  std::cin >> T;
  while (T--) {
    long double C;
    std::cin >> C;
    int n;
    std::cin >> n;
    long double g = 10;
    long double l = 0, r = 1e18;
    for (int i = 0; i < n; ++i) {
      long double x, y;
      std::cin >> x >> y;
      long double delta = C * C * C * C - g * g * x * x - 2 * g * C * C * y;
      delta = sqrtl(delta);
      l = std::max(l, (C * C - delta) / (g * x));
      r = std::min(r, (C * C + delta) / (g * x));
    }
    std::cout << (l + r) / 2 << "\n";
  }
}
