#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += a[i] > 0 && (i + 1 == n || a[i + 1] == 0);
    }
    std::cout << std::min(ans, 2) << "\n";
  }
}
