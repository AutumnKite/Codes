#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  int n;
  std::cin >> n;
  while (n--) {
    double p, c;
    std::cin >> p >> c;
    std::cout << 100 * p / (c + 100) << "\n";
  }
}
