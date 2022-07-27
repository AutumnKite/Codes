#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    std::string s;
    while (s.empty()) {
      std::getline(std::cin, s);
    }
    for (int i = 0; i < (int)s.size(); ++i) {
      if (i == 0 || s[i - 1] == ' ') {
        std::cout << char(s[i] - 'a' + 'A');
      }
    }
    std::cout << "\n";
  }
}
