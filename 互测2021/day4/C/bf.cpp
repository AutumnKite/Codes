#include <bits/stdc++.h>

const int P = 998244353;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, l, r, X;
  std::cin >> m >> l >> r >> X;
  std::string s;
  std::cin >> s;

  int n = X * m;
  for (int i = 0; i < m; ++i) {
    n += s[i] - '0';
  }

  int xor_sum = 0, pw = 1;
  int c = X * l;
  for (int k = 0; k < l; ++k) {
    c += s[k] - '0';
    pw = 233ll * pw % P;
  }
  for (int k = l; k <= r; ++k) {
    int ans = 0;
    std::vector<int> ansS;
    for (int S = 0; S < (1 << n); ++S) {
      if (__builtin_popcount(S) == c) {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
          int now = 0;
          for (int j = i; j < n; ++j) {
            now += S >> j & 1;
            cnt += now >= k;
          }
        }
        if (cnt > ans) {
          ans = cnt;
          ansS = std::vector<int>(1, S);
        } else if (cnt == ans) {
          ansS.push_back(S);
        }
      }
    }
    std::cerr << "c = " << c << ", k = " << k << ", ans = " << ans << "\n";
    for (int x : ansS) {
      int lst = -1;
      for (int i = 0; i < n; ++i) {
        if (x >> i & 1) {
          std::cerr << i - lst << " ";
          lst = i;
        }
      }
      std::cerr << n - lst << "\n";
    }
    xor_sum ^= 1ll * ans * pw % P;
    if (k < m) {
      c += X + s[k] - '0';
      pw = 233ll * pw % P;
    }
  }
  std::cout << xor_sum << "\n";
}
