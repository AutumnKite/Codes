#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    ans += x;
  }
  std::cout << ans << "\n";
}