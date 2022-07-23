#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    int m = 1;
    while (m * m < n) {
      ++m;
    }
    for (int i = 0; i < n; ++i) {
      std::cout << std::min(n, (i / m + 1) * m) - i % m << " \n"[i == n - 1];
    }
  }
}
