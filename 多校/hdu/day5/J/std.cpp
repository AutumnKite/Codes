#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> a(6), b(6);
    for (int i = 0; i < n; ++i) {
      int x;
      std::cin >> x;
      --x;
      ++a[x];
    }
    for (int i = 0; i < n; ++i) {
      int x;
      std::cin >> x;
      --x;
      ++b[x];
    }

    if (*std::max_element(a.begin(), a.end()) <= 1 &&
        *std::max_element(b.begin(), b.end()) <= 1) {
      std::cout << "Just a game of chance.\n";
    } else {
      std::cout << "Win!\n";
    }
  }
}