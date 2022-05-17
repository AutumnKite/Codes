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
    int m = *std::max_element(a.begin(), a.end());
    std::vector<int> c(m + 1);
    for (int i = 0; i < n; ++i) {
      ++c[a[i]];
    }
    long long ans = 0;
    for (int d = 1; d <= m; ++d) {
      for (int x = d; x + d <= m; x += d) {
        int y = x + d;
        if ((x ^ y) == d) {
          ans += 1ll * c[x] * c[y];
        }
      }
    }
    std::cout << ans << "\n";
  }
}
