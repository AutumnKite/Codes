#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> b[i];
  }

  std::cout << n << "\n";
  std::cout << 1 << " " << n << " I\n";
  std::sort(a.begin(), a.end());
  for (int i = 0; i < n - 1; ++i) {
    int j = std::find(a.begin(), a.end(), b[i]) - a.begin();
    if (a[j] < a[i]) {
      std::cout << i + 1 << " " << j + 1 << " I\n";
      std::sort(a.begin() + i, a.begin() + j + 1);
    } else {
      std::cout << i + 1 << " " << j + 1 << " D\n";
      std::sort(a.begin() + i, a.begin() + j + 1, std::greater<int>());
    }
  }
}
