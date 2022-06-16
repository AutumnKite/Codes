#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<bool> vis(1 << 17);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (vis[a[i] ^ a[j]]) {
        std::cout << "Yes\n";
        return 0;
      }
      vis[a[i] ^ a[j]] = true;
    }
  }
  std::cout << "No\n";
}
