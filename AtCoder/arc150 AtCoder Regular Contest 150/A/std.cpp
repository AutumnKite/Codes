#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m;
    std::string s;
    std::cin >> n >> m >> s;
    std::vector<int> pre0(n + 1), pre1(n + 1);
    for (int i = 0; i < n; ++i) {
      pre0[i + 1] = pre0[i] + (s[i] == '0');
      pre1[i + 1] = pre1[i] + (s[i] == '1');
    }
    int ans = 0;
    for (int i = 0; i + m <= n; ++i) {
      ans += pre0[i] == pre0[i + m] && pre1[i + m] - pre1[i] == pre1[n];
    }
    if (ans == 1) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
}