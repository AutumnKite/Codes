#include <bits/stdc++.h>

using i64 = int64_t;

class basis {
  int n;
  std::vector<i64> a;

public:
  basis(int t_n) : n(t_n), a(n) {}

  void insert(i64 x) {
    for (int i = n - 1; i >= 0; --i) {
      if (x >> i & 1) {
        if (!a[i]) {
          a[i] = x;
          return;
        }
        x ^= a[i];
      }
    }
  }

  i64 query() const {
    i64 res = 0;
    for (int i = n - 1; i >= 0; --i) {
      if (!(res >> i & 1) && a[i]) {
        res ^= a[i];
      }
    }
    return res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    basis B(50);
    for (int i = 0; i < n; ++i) {
      i64 x;
      std::cin >> x;
      B.insert(x);
    }
    std::cout << B.query() << "\n";
  }
}
