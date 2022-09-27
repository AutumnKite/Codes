#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    ans += !x;
  }
  for (int i = 0; i < m; ++i) {
    int x;
    std::cin >> x;
    ans += !x;
  }
  std::cout << std::abs(ans - m) << "\n";
}
