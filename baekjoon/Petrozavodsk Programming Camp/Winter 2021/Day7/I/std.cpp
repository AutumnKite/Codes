#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
    --b[i];
  }

  int cnt = std::accumulate(a.begin(), a.end(), 0);
  for (int i = 0; i < m; ++i) {
    if (cnt <= i) {
      std::cout << i << "\n";
      return 0;
    }
    cnt -= a[b[i]];
    a[b[i]] ^= 1;
    cnt += a[b[i]];
  }
  std::cout << std::max(cnt, m) << "\n";
}
