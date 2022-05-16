#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;

  std::multiset<int> S;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'R') {
      int l = 1;
      while (i - l >= 0 && i + l < n && s[i - l] == 'A' && s[i + l] == 'C') {
        ++l;
      }
      if (l > 1) {
        S.insert(l - 1);
      }
    }
  }

  int ans = 0;
  while (!S.empty()) {
    if (ans & 1) {
      S.erase(S.begin());
      ++ans;
    } else {
      auto it = --S.end();
      int x = *it;
      --x;
      S.erase(it);
      if (x) {
        S.insert(x);
      }
      ++ans;
    }
  }
  std::cout << ans << "\n";
}