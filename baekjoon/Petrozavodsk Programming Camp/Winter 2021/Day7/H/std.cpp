#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::pair<long long, int>> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i].first;
    a[i].second = i;
  }
  std::sort(a.begin(), a.end());

  std::vector<int> suf(n + 1);
  suf[n] = n;
  for (int i = n - 1; i >= 0; --i) {
    suf[i] = std::min(suf[i + 1], a[i].second);
  }
  long long ans = 0;
  int max = 0;
  for (int i = 0; i < n; ++i) {
    max = std::max(max, a[i].second);
    if (max > suf[i + 1]) {
      ans = std::max(ans, a[i + 1].first - a[i].first);
    }
  }
  std::cout << ans << "\n";
}
