#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  int p = 0;
  while (p * (p + 1) / 2 < n) {
    ++p;
  }
  std::vector<int> ans;
  while (p > 0) {
    if (n >= p) {
      std::cout << p << "\n";
      n -= p;
    }
    --p;
  }
}
