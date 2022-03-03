#include <bits/stdc++.h>

std::mt19937_64 rnd(
    std::chrono::system_clock::now().time_since_epoch().count());

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T = 10000;
  std::cout << T << "\n";
  while (T--) {
    int n = rnd() % 3 + 8;
    std::cout << n << "\n";
    for (int i = 0; i < n - 1; ++i) {
      std::cout << rnd() % (i + 1) + 1 << " " << i + 2 << "\n";
    }
  }
}
