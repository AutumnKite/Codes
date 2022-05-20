#include <bits/stdc++.h>

int solve(int x) {
  int res = 0;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      ++res;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  return res + (x > 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int x;
    std::cin >> x;
    std::cout << solve(x) + solve(x + 1) << "\n";
  }
}
