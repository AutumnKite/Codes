#include <bits/stdc++.h>

constexpr int INF = std::numeric_limits<int>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> sum(1 << n);
  for (int i = 0; i < n; ++i) {
    sum[1 << i] = a[i];
  }
  for (int S = 1; S < (1 << n); ++S) {
    sum[S] = sum[S & (S - 1)] + sum[S & -S];
  }

  std::vector<int> f(1 << n, INF);
  f[0] = -INF;
  for (int S = 1; S < (1 << n); ++S) {
    for (int i = 0; i < n; ++i) {
      if (S >> i & 1 && sum[S ^ (1 << i)] >= 0) {
        f[S] = std::min(f[S], std::max(f[S ^ (1 << i)], sum[S]));
      }
    }
  }
  
  std::vector<int> g(1 << n, INF);
  g[0] = -INF;
  for (int S = 1; S < (1 << n); ++S) {
    for (int T = S; T; T = (T - 1) & S) {
      if (sum[T] < 0) {
        g[S] = std::min(g[S], std::max(g[S ^ T], f[T]));
      }
    }
  }

  int U = (1 << n) - 1;
  int ans = INF;
  for (int S = 0; S < (1 << n); ++S) {
    ans = std::min(ans, std::max(g[S], f[U ^ S]));
  }
  std::cout << ans << "\n";
}
