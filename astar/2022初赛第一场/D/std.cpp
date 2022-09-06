#include <bits/stdc++.h>

const int INF = std::numeric_limits<int>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, L, q;
  std::cin >> n >> m >> L >> q;
  std::vector<std::vector<int>> a(n, std::vector<int>(m, INF));
  for (int i = 0; i < q; ++i) {
    int x, y, t;
    std::cin >> x >> y >> t;
    --x, --y;
    a[x][y] = std::min(a[x][y], t);
  }
  std::vector<std::vector<int>> b(n, std::vector<int>(m - L + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= m - L; ++j) {
      for (int k = j; k < j + L; ++k) {
        b[i][j] = std::max(b[i][j], a[i][k]);
      }
    }
  }
  int ans = INF;
  for (int i = 0; i <= n - L; ++i) {
    for (int j = 0; j <= m - L; ++j) {
      int max = 0;
      for (int k = i; k < i + L; ++k) {
        max = std::max(max, b[k][j]);
      }
      ans = std::min(ans, max);
    }
  }
  if (ans == INF) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }
}
