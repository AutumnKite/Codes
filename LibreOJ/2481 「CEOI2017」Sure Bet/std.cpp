#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(4);

  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    double ta, tb;
    std::cin >> ta >> tb;
    a[i] = ta * 10000 + 0.5, b[i] = tb * 10000 + 0.5;
  }

  std::sort(a.begin(), a.end(), std::greater<int>());
  std::sort(b.begin(), b.end(), std::greater<int>());

  std::vector<long long> sa(n + 1), sb(n + 1);
  for (int i = 0; i < n; ++i) {
    sa[i + 1] = sa[i] + a[i];
    sb[i + 1] = sb[i] + b[i];
  }

  long long ans = 0;
  for (int i = 0, j = 0; i <= n; ++i) {
    while (j <= n && sb[j] < sa[i]) {
      ++j;
    }
    if (j == n + 1) {
      break;
    }
    ans = std::max(ans, sa[i] - 10000 * (i + j));
  }
  for (int i = 0, j = 0; i <= n; ++i) {
    while (j <= n && sa[j] < sb[i]) {
      ++j;
    }
    if (j == n + 1) {
      break;
    }
    ans = std::max(ans, sb[i] - 10000 * (i + j));
  }
  std::cout << 1.0 * ans / 10000 << "\n";
}