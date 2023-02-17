#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);
  
  int T;
  std::cin >> T;
  while (T--) {
    int n;
    i64 v;
    std::cin >> n >> v;
    std::vector<i64> p(n), w(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> p[i] >> w[i];
    }
    double l = 0, r = 1e12;
    for (int t = 0; t < 100; ++t) {
      double m = (l + r) / 2;
      double a = 1e100, b = 1e100;
      for (int i = 0; i < n; ++i) {
        if (p[i] > 0) {
          a = std::min(a, p[i] - w[i] * m);
        } else {
          b = std::min(b, -p[i] - w[i] * m);
        }
      }
      if (a + b <= 0) {
        r = m;
      } else {
        l = m;
      }
    }
    std::cout << r * v << "\n";
  }
}
