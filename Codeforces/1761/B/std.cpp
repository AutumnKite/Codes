#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      ok &= a[i] == a[i & 1];
    }
    if (ok) {
      std::cout << n / 2 + 1 << "\n";
    } else {
      std::cout << n << "\n";
    }
  }
}
