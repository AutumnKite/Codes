#include <bits/stdc++.h>

std::mt19937_64 rnd(
    std::chrono::system_clock::now().time_since_epoch().count());

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 6, m = 1;
  std::cout << n << "\n";
  for (int i = 1; i < n; ++i) {
    std::cout << rnd() % i + 1 << " " << i + 1 << "\n";
  }
  std::cout << m << "\n";
  for (int i = 0; i < m; ++i) {
    std::cout << rnd() % n + 1 << " " << rnd() % n + 1 << " "
              << rnd() % n << "\n";
  }
}
