#include <bits/stdc++.h>

#define plus(a, b) (a + b >= n ? a + b - n : a + b)
#define minus(a, b) (a < b ? a + n - b : a - b)

int cnt[500][500][500];

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, r;
  std::cin >> n >> r;
  for (int i = 0; i < n; ++i) {
    for (int j = 0, a = 0; j < n; ++j, a = plus(a, i)) {
      for (int k = 0, b = 0, c = 0; k < n; ++k, b = plus(b, j), c = plus(c, i)) {
        ++cnt[a][b][c];
      }
    }
  }
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0, a = r; j < n; ++j, a = minus(a, i)) {
      for (int k = 0, b = r, c = r; k < n; ++k, b = minus(b, j), c = minus(c, i)) {
        ans += cnt[a][b][c];
      }
    }
  }
  std::cout << ans << "\n";
}
