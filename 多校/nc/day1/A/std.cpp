#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> a;
  for (int i = 0; i < n; ++i) {
    int x, r;
    std::cin >> x >> r;
    a.emplace_back(x - r, x + r);
  }
  std::sort(a.begin(), a.end());
  int ans = 0;
  int now = a[0].second;
  for (int i = 1; i < n; ++i) {
    if (a[i].first <= now) {
      now = std::max(now, a[i].second);
    } else {
      ans += a[i].first - now;
      now = a[i].second;
    }
  }
  std::cout << ans << "\n";
}
