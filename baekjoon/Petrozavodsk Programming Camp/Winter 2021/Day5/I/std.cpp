#include <bits/stdc++.h>

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n, S;
  std::cin >> n >> S;
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i].second;
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i].first;
  }
  std::sort(a.begin(), a.end());
  std::reverse(a.begin(), a.end());

  int L = std::min(n, 2000);
  std::vector<long long> f(L + 1, INF);
  f[0] = 0;
  for (auto [p, c] : a) {
    for (int j = L; j >= 1; --j) {
      f[j] = std::min(f[j], f[j - 1] + 1ll * p * (j - 1) + c);
    }
  }
  std::cout << std::upper_bound(f.begin(), f.end(), S) - f.begin() - 1 << "\n";
}
