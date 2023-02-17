#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int T;
  std::cin >> T;
  while (T--) {
    std::string s;
    std::cin >> s;
    int ans = 0;
    for (int i = 3; i < (int)s.size(); ++i) {
      if (s.substr(i - 3, 4) == "ania") {
        s[i] = 'b';
        ++ans;
      }
    }
    std::cout << ans << "\n";
  }
}
