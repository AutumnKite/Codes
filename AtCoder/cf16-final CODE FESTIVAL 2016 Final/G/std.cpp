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

  int n, q;
  std::cin >> n >> q;
  std::priority_queue<std::tuple<int, int, int>> Q;
  for (int i = 0; i < q; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    Q.emplace(-w, u, v);
    Q.emplace(-(w + 1), v, (u + 1) % n);
  }

  disjoint_set D(n);
  int now = n;
  long long ans = 0;
  while (now > 1) {
    auto [w, u, v] = Q.top();
    Q.pop();
    w = -w;
    if (D.merge(u, v)) {
      --now;
      ans += w;
      w += 2;
      Q.emplace(-w, (u + 1) % n, (v + 1) % n);
    }
  }
  std::cout << ans << "\n";
}
