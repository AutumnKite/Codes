#include <bits/stdc++.h>

using u64 = uint64_t;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<u64> h(n + 1), pw(n + 1);
    pw[0] = 1;
    for (int i = 0; i < n; ++i) {
      h[i + 1] = h[i] * 233 + s[i];
      pw[i + 1] = pw[i] * 233;
    }

    auto substr = [&](int l, int r) {
      return h[r] - h[l] * pw[r - l];
    };

    int l = 0, r = n, ans = 0;
    while (l < r) {
      int len = 1;
      while (substr(l, l + len) != substr(r - len, r)) {
        ++len;
      }
      if (l + len == r) {
        ++ans;
      } else {
        ans += 2;
      }
      l += len;
      r -= len;
    }
    std::cout << ans << "\n";
  }
}
