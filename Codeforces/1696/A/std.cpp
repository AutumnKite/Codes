#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, v;
    std::cin >> n >> v;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      a[i] |= v;
    }
    std::cout << *std::max_element(a.begin(), a.end()) << "\n";
  }
}
