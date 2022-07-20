#include <bits/stdc++.h>

const int N = 1 << 10;

using bits = std::bitset<N>;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m;
    std::cin >> n >> m;
    std::vector<bits> f(N);
    f[0][0] = 1;
    for (int i = 0; i < n; ++i) {
      int v, w;
      std::cin >> v >> w;
      auto g = f;
      for (int j = 0; j < N; ++j) {
        g[w ^ j] |= f[j] << v;
      }
      f.swap(g);
    }
    int ans = N - 1;
    while (ans >= 0 && !f[ans][m]) {
      --ans;
    }
    std::cout << ans << "\n";
  }
}
