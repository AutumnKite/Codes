#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::set<std::pair<int, int>> S;
  for (int k = 1; k <= std::max(n, m); k += 2) {
    for (int i = std::min(k, n); i <= std::min(k + 2, n); ++i) {
      for (int j = std::min(k, m); j <= std::min(k + 2, m); ++j) {
        S.emplace(i, j);
      }
    }
  }
  std::cout << S.size() << "\n";
  for (auto [x, y] : S) {
    std::cout << x << " " << y << "\n";
  }
}
