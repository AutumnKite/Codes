#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int sub, T;
  std::cin >> sub >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> b[i];
    }
    if (sub == 2) {
      for (int i = 0; i < n; ++i) {
        std::cout << i + 1 << " \n"[i == n - 1];
      }
      continue;
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);

    auto check = [&]() {
      for (int k = 0; k < n; ++k) {
        auto a = p;
        a.erase(a.begin() + k);
        std::vector<int> dis(a.size(), a.size());
        dis[0] = 0;
        for (int i = 0; i < (int)a.size(); ++i) {
          if (dis[i] != (int)a.size()) {
            int min = a[i], max = a[i];
            for (int j = i + 1; j < (int)a.size(); ++j) {
              min = std::min(min, a[j]);
              max = std::max(max, a[j]);
              if (min == std::min(a[i], a[j]) && max == std::max(a[i], a[j])) {
                dis[j] = std::min(dis[j], dis[i] + 1);
              }
            }
          }
        }
        if (dis.back() != b[k]) {
          return false;
        }
      }
      return true;
    };

    while (!check()) {
      std::next_permutation(p.begin(), p.end());
    }
    for (int i = 0; i < n; ++i) {
      std::cout << p[i] + 1 << " \n"[i == n - 1];
    }
  }
}
/*
9 1
4
2 2 1 1
*/
