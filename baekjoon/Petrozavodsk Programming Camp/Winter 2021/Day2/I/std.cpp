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
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
      int x;
      std::cin >> x;
      a[i] = x - a[i];
      sum += a[i];
    }
    if (n == 1) {
      std::cout << "YES\n";
    } else if (a[0] == 0 || (n == 2 && a[1] > 0) || sum < n - 1) {
      std::cout << "NO\n";
    } else {
      std::cout << "YES\n";
    }
  }
}
