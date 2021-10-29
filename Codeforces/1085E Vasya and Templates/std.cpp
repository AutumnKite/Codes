#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    std::string s, a, b;
    std::cin >> s >> a >> b;
    int n = s.size();
    int l = 0;
    std::vector<int> p(26, -1);
    std::vector<bool> vis(26);
    while (l < n && a[l] == b[l]) {
      ++l;
    }
    for (int i = l; i < n; ++i) {
      if ()
    }
  }
}
