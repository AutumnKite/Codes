#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    std::string s;
    std::cin >> s;
    int c[2][2] = {};
    for (int i = 0; i < (int)s.size(); ++i) {
      ++c[i & 1][s[i] - '0'];
    }
    for (int i = 0; i < (int)s.size(); ++i) {
      if (c[i & 1][0]) {
        std::cout << 0;
        --c[i & 1][0];
      } else {
        std::cout << 1;
      }
    }
    std::cout << "\n";
  }
}