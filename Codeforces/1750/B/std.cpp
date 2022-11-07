#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    int len = 0, cnt = 0;
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
      ++len;
      cnt += s[i] - '0';
      if (i + 1 == n || s[i] != s[i + 1]) {
        ans = std::max(ans, 1ll * len * len);
        len = 0;
      }
    }
    ans = std::max(ans, 1ll * cnt * (n - cnt));
    std::cout << ans << "\n";
  }
}