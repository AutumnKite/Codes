#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  auto check = [&](int n, int m, int k) {
    if (k < std::max(n / 2, m / 2)) {
      return false;
    }
    if (k > n * m / 4) {
      return false;
    }
    if (k == n * m / 4 - 1) {
      return false;
    }
    if (n == m && k == n / 2 + 1) {
      return false;
    }
    return true;
  };

  for (int n = 2; n <= 100; n += 2) {
    for (int m = n; m <= 100; m += 2) {
      for (int k = 0; k <= 10000; ++k) {
        if (check(n, m, k) != (check(n - 2, m - 2, k - 1) || check(n, m - 2, k - n / 2))) {
          std::cout << "shit\n";
          return 0;
        }
      }
    }
  }
  std::cout << "OK\n";
}
