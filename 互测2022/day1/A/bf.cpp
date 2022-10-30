#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<int> cnt0(n + 1), cnt1(n + 1);
  for (int i = 0; i < n; ++i) {
    cnt0[i + 1] = cnt0[i] + (s[i] == '0');
    cnt1[i + 1] = cnt1[i] + (s[i] == '1');
  }
  int ans = 0;
  std::vector<int> f(n + 1);
  for (int i = 0; i <= n; ++i) {
    f[i] = std::max(cnt0[i], cnt1[i]);
    ans = std::max(ans, cnt0[i] + cnt1[n] - cnt1[i]);
  }
  std::cout << ans;
  for (int k = 1; k <= n; ++k) {
    std::vector<int> g(n + 1);
    int max0 = 0, max1 = 0;
    for (int i = 0; i <= n; ++i) {
      max0 = std::max(max0, f[i] - cnt0[i]);
      max1 = std::max(max1, f[i] - cnt1[i]);
      g[i] = std::max(max0 + cnt0[i], max1 + cnt1[i]);
    }
    f.swap(g);
    if (k > 1) {
      std::cout << " " << f[n];
    }
  }
  std::cout << "\n";
}
