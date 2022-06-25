#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, v;
    std::cin >> n >> v;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    int m;
    std::cin >> m;
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) {
      std::cin >> b[i];
    }

    auto change = [&](std::vector<int> a) {
      std::vector<std::pair<int, long long>> res;
      for (int i = 0; i < (int)a.size(); ++i) {
        long long c = 1;
        int x = a[i];
        while (x % v == 0) {
          x /= v;
          c *= v;
        }
        if (res.empty() || res.back().first != x) {
          res.emplace_back(x, c);
        } else {
          res.back().second += c;
        }
      }
      return res;
    };

    if (change(a) == change(b)) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
}
