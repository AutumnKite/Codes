#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> f(m, -1);
  int ans = n + 1;
  for (int i = 0; i < n; ++i) {
    f[0] = i;
    std::vector<int> g(f);
    int l;
    std::cin >> l;
    for (int j = 0; j < l; ++j) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      g[v] = std::max(g[v], f[u]);
    }
    f.swap(g);
    if (f[m - 1] != -1) {
      ans = std::min(ans, i - f[m - 1] + 1);
    }
  }
  if (ans == n + 1) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }
}
