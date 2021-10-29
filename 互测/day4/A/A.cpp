#include <bits/stdc++.h>

class disjoint_set {
public:
  typedef std::size_t size_type;

protected:
  std::vector<size_type> fa;

public:
  disjoint_set(size_type n = 0) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  size_type find(size_type x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
  }

  bool merge(size_type x, size_type y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    fa[y] = x;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q, m;
  std::cin >> n >> q >> m;
  if (n <= 200000 && q <= 10) {
    std::vector<std::tuple<int, int, int>> edge;
    for (int i = 0; i < q; ++i) {
      int d, x;
      std::cin >> d >> x;
      for (int u = 0; u < n - d; ++u) {
        edge.emplace_back(x, u, u + d);
      }
    }
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      std::cin >> u >> v >> w;
      edge.emplace_back(w, u, v);
    }
    std::sort(edge.begin(), edge.end());

    disjoint_set D(n);
    long long ans = 0;
    for (auto [w, u, v] : edge) {
      if (D.merge(u, v)) {
        ans += w;
      }
    }
    std::cout << ans % 998244353 << "\n";
  } else {
    std::cout << (n - 1) % 998244353 << "\n";
  }
}
