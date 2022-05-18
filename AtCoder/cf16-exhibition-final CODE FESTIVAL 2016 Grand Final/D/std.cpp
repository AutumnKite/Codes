#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  int a[2][6];
  for (int k = 0; k < 2; ++k) {
    for (int i = 0; i < 6; ++i) {
      std::cin >> a[k][i];
    }
  }

  double ans = 1;
  for (int t = 0; t < 6; ++t) {
    for (int l = 0; l < 2; ++l) {
      double k = 1.0 * a[l][t] / (a[0][t] + a[1][t]);
      double d = 0;
      for (int i = 0; i < 6; ++i) {
        d += std::max(1.0 * a[0][i] / 100 * k, 1.0 * a[1][i] / 100 * (1 - k));
      }
      ans = std::min(ans, d);
    }
  }
  std::cout << ans << "\n";
}
