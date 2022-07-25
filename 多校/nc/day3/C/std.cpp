#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
  }
  std::sort(s.begin(), s.end(),
            [&](const std::string &a, const std::string &b) {
              return a + b < b + a;
            });
  for (const auto &p : s) {
    std::cout << p;
  }
  std::cout << "\n";
}
