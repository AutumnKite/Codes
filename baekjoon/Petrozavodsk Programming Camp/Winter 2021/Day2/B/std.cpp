#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  
  if (n % 4 > 1) {
    std::cout << "NO\n";
    return 0;
  }

  if (n == 1) {
    std::cout << "YES\n";
    std::cout << 0 << "\n";
    return 0;
  }

  if (n == 5) {
    std::cout << "YES\n";
    std::cout << 2 << " " << 4 << " " << 1 << " " << 3 << " " << 0 << "\n";
    return 0;
  }

  if (n % 4 == 0) {
    std::cout << "YES\n";
    int m = n / 4;
    std::cout << 2 * m << " ";
    for (int i = 1; i < m; ++i) {
      std::cout << 4 * m - i << " ";
    }
    for (int i = 1; i < m; ++i) {
      std::cout << 3 * m - i << " ";
    }
    for (int i = 1; i <= m; ++i) {
      std::cout << 2 * m - i << " ";
    }
    std::cout << 3 * m << " ";
    for (int i = 1; i < m; ++i) {
      std::cout << m - i << " ";
    }
    std::cout << 0 << "\n";
    return 0;
  }

  if (n % 4 == 1) {
    std::cout << "YES\n";
    int m = (n - 1) / 4;
    std::cout << 2 * m - 1 << " ";
    for (int i = 0; i < m; ++i) {
      std::cout << 4 * m - i << " ";
    }
    for (int i = 1; i <= m; ++i) {
      std::cout << 3 * m - i << " ";
    }
    for (int i = 2; i < m; ++i) {
      std::cout << 2 * m - i << " ";
    }
    std::cout << 3 * m << " ";
    for (int i = 0; i < m; ++i) {
      std::cout << m - i << " ";
    }
    std::cout << 0 << "\n";
    return 0;
  }
}
