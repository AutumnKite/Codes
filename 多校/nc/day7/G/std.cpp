#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    std::string s;
    std::cin >> s;
    if (s.size() == 1) {
      std::cout << 1 << " " << 2 << "\n";
      continue;
    }
    bool ok = true;
    for (char c : s) {
      ok *= c == s[0];
    }
    std::cout << 2 << " " << ok * 2 + (s.size() == 2) * 4 + 2 << "\n";
  }
}
