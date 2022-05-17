#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    std::size_t n;
    char c;
    std::cin >> n >> c;
    std::string a, b;
    std::cin >> a >> b;
    
    if (a >= b) {
      std::cout << "NO\n";
      continue;
    }

    auto next = [&]() {
      while (a.back() == 'z') {
        a.pop_back();
      }
      ++a.back();
      while (a.size() < n) {
        a.push_back('a');
      }
    };

    next();
    bool ok = false;
    while (a < b) {
      if (std::find(a.begin(), a.end(), c) != a.end()) {
        std::cout << a << "\n";
        ok = true;
        break;
      }
      next();
    }
    if (!ok) {
      std::cout << "NO\n";
    }
  }
}
