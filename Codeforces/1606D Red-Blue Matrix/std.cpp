#include <bits/stdc++.h>

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> a(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> a[i][j];
    }
  }
  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    return a[x][0] < a[y][0];
  }); 
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    solve();
  }
}
