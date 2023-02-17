#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::string> a(n), b(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i] >> b[i];
    }
    int ansx = 0, ansy = 0, ansz = 6;
    for (int x = 0; x <= 5; ++x) {
      for (int y = 0; x + y <= 5; ++y) {
        std::map<std::string, int> mp;
        for (int i = 0; i < n; ++i) {
          ++mp[a[i].substr(0, x) + b[i].substr(0, y)];
        }
        int max = 0;
        for (const auto &p : mp) {
          max = std::max(max, p.second);
        }
        --max;
        int z = 0;
        while (max > 0) {
          max /= 10;
          ++z;
        }
        if (!x && !y && !z) {
          z = 1;
        }
        if (x + y + z < ansx + ansy + ansz) {
          ansx = x, ansy = y, ansz = z;
        }
      }
    }
    std::cout << ansx << " " << ansy << " " << ansz << "\n";
  }
}
