#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int sub;
  std::cin >> sub;
  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  if (sub == 1) {
    while (q--) {
      int op;
      std::cin >> op;
      if (op == 1) {
        int l, r;
        std::cin >> l >> r;
        for (int i = r - 1; i >= l; --i) {
          a[i] ^= a[i - 1];
        }
      } else {
        int pos;
        std::cin >> pos;
        --pos;
        std::cout << a[pos] << "\n";
      }
    }
    for (int x : a) {
      std::cout << x << "\n";
    }
  } else {
    const int B = 7;
    std::vector<std::vector<int>> f(1 << B, std::vector<int>(n));
    f[0] = a;
    for (int S = 1; S < (1 << B); ++S) {
      int L = S & -S;
      for (int i = 0; i < n; ++i) {
        f[S][i] = f[S ^ L][i] ^ (i >= L ? f[S ^ L][i - L] : 0);
      }
    }

    auto query = [&](int S, int i) {
      int L = S & ((1 << B) - 1);
      S ^= L;
      int ans = 0;
      for (int T = S; ; T = (T - 1) & S) {
        if (i >= T) {
          ans ^= f[L][i - T];
        }
        if (!T) {
          break;
        }
      }
      return ans;
    };

    int k = 0;
    while (q--) {
      int op;
      std::cin >> op;
      if (op == 1) {
        int l, r;
        std::cin >> l >> r;
        ++k;
      } else {
        int pos;
        std::cin >> pos;
        --pos;
        std::cout << query(k, pos) << "\n";
      }
    }
    for (int i = 0; i < n; ++i) {
      std::cout << query(k, i) << "\n";
    }
  }
}
