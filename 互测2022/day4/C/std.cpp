#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  // T = 1 << 9;
  while (T--) {
    int n;
    std::cin >> n;
    // n = 9;
    std::vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      // a[i] = T >> i & 1;
      sum ^= a[i];
    }
    if (sum == 0) {
      std::cout << "Draw\n";
      continue;
    }
    int k = std::__lg(sum);
    for (int i = 0; i < n; ++i) {
      a[i] = a[i] >> k & 1;
    }

    // auto dfs = [&](auto &self, int l, int r, int x, int y) -> bool {
    //   if (l == r) {
    //     return x;
    //   }
    //   if (!self(self, l + 1, r, y, x ^ a[l])) {
    //     return true;
    //   }
    //   if (!self(self, l, r - 1, y, x ^ a[r - 1])) {
    //     return true;
    //   }
    //   return false;
    // };

    if (n % 2 == 0) {
      std::cout << "First\n";
      continue;
    }
    int c1 = 0;
    for (int i = 1; i < n; i += 2) {
      c1 ^= a[i];
    }
    if (c1) {
      std::cout << "Second\n";
      continue;
    }

    auto check = [&](int l, int r) {
      while (l < r && a[l] == a[r - 1]) {
        ++l, --r;
      }
      while (l < r && a[l] == a[l + 1]) {
        ++l, ++l;
      }
      return l == r;
    };

    if ((a[0] && check(1, n)) || (a[n - 1] && check(0, n - 1))) {
      std::cout << "First\n";
    } else {
      std::cout << "Second\n";
    }
  }
}
