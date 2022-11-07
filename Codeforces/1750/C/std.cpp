#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;
    bool p = a[0] != b[0], ok = true;
    for (int i = 0; i < n; ++i) {
      if ((a[i] != b[i]) != p) {
        ok = false;
        break;
      }
    }
    if (!ok) {
      std::cout << "NO\n";
      continue;
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      cnt += a[i] - '0';
    }
    std::vector<std::pair<int, int>> ans;
    if ((cnt & 1) != p) {
      a[0] ^= 1, a[1] ^= 1;
      ans.emplace_back(0, 2);
    }
    for (int i = 0; i < n; ++i) {
      if (a[i] == '1') {
        ans.emplace_back(i, i + 1);
      }
    }
    std::cout << "YES\n";
    std::cout << ans.size() << "\n";
    for (auto [l, r] : ans) {
      std::cout << l + 1 << " " << r << "\n";
    }
  }
}