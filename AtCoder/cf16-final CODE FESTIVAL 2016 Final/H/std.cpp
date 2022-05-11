#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  --n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int sum = std::accumulate(a.begin(), a.end(), 0);

  std::deque<int> f(sum + 1);
  std::iota(f.begin(), f.end(), 0);
  for (int i = 2; i < n; ++i) {
    std::vector<int> sta;
    for (int j = 1; j <= a[i]; ++j) {
      sta.push_back(f[j]);
    }
    f.resize(sum - a[i] + 1);
    f.insert(f.begin(), sta.rbegin(), sta.rend());
  }

  int m;
  std::cin >> m;
  while (m--) {
    int x;
    std::cin >> x;
    if (x > sum) {
      std::cout << x + a[0] - (sum - a[0]) << "\n";
    } else {
      std::cout << f[x] + a[0] - a[1] << "\n";
    }
  }
}
