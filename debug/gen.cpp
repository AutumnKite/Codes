#include <bits/stdc++.h>

std::mt19937_64 rnd(
    std::chrono::system_clock::now().time_since_epoch().count());

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 500, m = 500;
  std::cout << n << " " << m << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << rnd() % 1 + 1 << " \n"[i == n - 1];
  }
  for (int i = 0; i < m; ++i) {
    std::cout << rnd() % 1 + 1 << " \n"[i == m - 1];
  }
  for (int i = 1; i < n; ++i) {
    std::cout << 1 << " " << i + 1 << "\n";
  }
  for (int i = 1; i < m; ++i) {
    std::cout << i << " " << i + 1 << "\n";
  }
}
