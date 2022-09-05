#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    --a[i];
    b[i] = (a[i] & 1) ^ (i & 1);
  }
  std::vector<std::pair<int, int>> ans;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - 2; ++j) {
      if (b[j] < b[j + 2]) {
        ans.emplace_back(0, j);
        std::swap(b[j], b[j + 2]);
        std::swap(a[j], a[j + 2]);
      }
    }
  }
  for (int i = 0; i < n - 1; i += 2) {
    if (b[i] && b[i + 1]) {
      ans.emplace_back(1, i);
      std::swap(a[i], a[i + 1]);
    } else {
      break;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n - 2; ++j) {
      if (a[j] > a[j + 2]) {
        ans.emplace_back(0, j);
        std::swap(a[j], a[j + 2]);
      }
    }
  }
  std::cout << ans.size() << "\n";
  for (auto p : ans) {
    if (p.first) {
      std::cout << "A " << p.second + 1 << "\n";
    } else {
      std::cout << "B " << p.second + 1 << "\n";
    }
  }
}
