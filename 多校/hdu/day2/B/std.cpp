#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    std::string s;
    std::cin >> s;
    for (char c : s) {
      if ((c < 'a' || c > 'z') && c != 58 && c != 95) {
        std::cout << c;
      }
    }
    std::cout << "\n";
  }
}
// https://www.luogu.com.cn/paste/l3eqj46t