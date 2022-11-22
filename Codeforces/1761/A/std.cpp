#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, a, b;
    std::cin >> n >> a >> b;
    if ((a == n && b == n) || a + b < n - 1) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
}
