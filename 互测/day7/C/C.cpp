#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  std::vector<unsigned long long> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> fa(n), dep(n);
  
  auto dfs = [&](auto &self, int u) -> void {
    for (int v : E[u]) {
      if (v != fa[u]) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        self(self, v);
      }
    }
  };

  dfs(dfs, 0);

  int q;
  std::cin >> q;
  unsigned long long ans = 0;
  std::vector<unsigned long long> val;
  val.reserve(n);
  while (q--) {
    int x, y, m;
    std::cin >> x >> y >> m;
    x = (x ^ ans) % n, y = (y ^ ans) % n;
    while (dep[x] > dep[y]) {
      val.push_back(a[x]);
      x = fa[x];
    }
    while (dep[x] < dep[y]) {
      val.push_back(a[y]);
      y = fa[y];
    }
    while (x != y) {
      val.push_back(a[x]);
      val.push_back(a[y]);
      x = fa[x];
      y = fa[y];
    }
    val.push_back(a[x]);
    ans = 0;
    for (int i = 61; i >= 0; --i) {
      int cnt = 0;
      for (auto x : val) {
        cnt += x >> i & 1;
      }
      if (cnt >= m) {
        ans |= 1ull << i;
        auto it = val.begin();
        for (auto x : val) {
          if (x >> i & 1) {
            *it++ = x;
          }
        }
        val.resize(it - val.begin());
      }
    }
    val.clear();
    std::cout << ans << "\n";
  }
}
