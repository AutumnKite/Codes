#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<bool> vis(30);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    sum ^= x;
    vis[std::__lg(x & -x)] = true;
  }
  int ans = 0;
  for (int i = 29; i >= 0; --i) {
    if (sum >> i & 1) {
      if (vis[i]) {
        sum ^= (1 << (i + 1)) - 1;
        ++ans;
      } else {
        std::cout << -1 << "\n";
        return 0;
      }
    }
  }
  std::cout << ans << "\n";
}
