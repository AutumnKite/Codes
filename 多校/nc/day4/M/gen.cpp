#include <bits/stdc++.h>

std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = rnd() % 6 + 1;
  std::cout << n << "\n";
  for (int i = 0; i < n; ++i) {
    int x = rnd() % 11 - 5, y = rnd() % 11 - 5;
    std::cout << x << " " << y << "\n";
  }
}
