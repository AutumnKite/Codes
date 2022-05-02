#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  long long now = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    int k = 0;
    while (k < x || now >> k & 1) {
      if (now >> k & 1) {
        now ^= 1ll << k;
      }
      ++k;
    }
    now ^= 1ll << k;
    if (x != k) {
      now ^= 1ll << x;
    }
  }
  std::cout << now << "\n";
}
