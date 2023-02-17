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
    auto check = [&](int i, int j, int k) {
      return 1ll * (a[k] - a[j]) * (j - i) < 1ll * (a[j] - a[i]) * (k - j);
    };
    std::vector<int> sta;
    for (int i = 0; i < n; ++i) {
      while (sta.size() > 1 && !check(sta.rbegin()[1], sta.rbegin()[0], i)) {
        sta.pop_back();
      }
      sta.push_back(i);
    }
    long long ans = 0;
    for (int i = 0; i + 1 < (int)sta.size(); ++i) {
      ans += 1ll * (a[sta[i]] + a[sta[i + 1]]) * (sta[i + 1] - sta[i]);
    }
    std::cout << ans << "\n";
  }
}
