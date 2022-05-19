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

  int n0, m0, n1, m1;
  std::cin >> n0 >> m0 >> n1 >> m1;
  std::vector<std::tuple<int, int, int, int>> edge;
  for (int i = 0; i < m0; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edge.emplace_back(w, u, v, 0);
  }
  for (int i = 0; i < m1; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edge.emplace_back(w, u, v, 1);
  }
  std::sort(edge.begin(), edge.end());

  disjoint_set D0(n0), D1(n1);
  int c0 = n0, c1 = n1;
  long long ans = 0;
  for (auto [w, u, v, op] : edge) {
    if (op == 0) {
      if (D0.merge(u, v)) {
        --c0;
        ans += 1ll * w * c1;
      }
    } else {
      if (D1.merge(u, v)) {
        --c1;
        ans += 1ll * w * c0;
      }
    }
  }
  std::cout << ans << "\n";
}
