#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;
  std::string a;
  std::cin >> a;

  for (int d = 1; d <= n; ++d) {
    if (n % d == 0) {
      std::vector<std::array<int, 26>> cnt(d);
      for (int i = 0; i < n; ++i) {
        ++cnt[i % d][a[i] - 'a'];
      }
      int sum = 0;
      for (int i = 0; i < d; ++i) {
        sum += n / d - *std::max_element(cnt[i].begin(), cnt[i].end());
      }
      if (sum <= k) {
        std::cout << d << "\n";
        return 0;
      }
    }
  }
}