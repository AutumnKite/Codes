#include <bits/stdc++.h>

template<typename Val, 
         typename VV = std::plus<Val>>
class fenwick_tree {
public:
  typedef std::size_t size_type;

protected:
  const Val E;

  size_type n;
  std::vector<Val> val;

  VV fun;

public:
  fenwick_tree() : fenwick_tree(0) {}

  fenwick_tree(size_type _n)
  : E(), n(_n), val(n + 1, E) {}

  fenwick_tree(size_type _n, const Val &_E)
  : E(_E), n(_n), val(n + 1, E) {}

  size_type size() const {
    return n;
  }

  void modify(size_type x, const Val &v) {
    for (++x; x <= n; x += x & -x) {
      val[x] = fun(val[x], v);
    }
  }

  Val query(size_type x) {
    Val s = E;
    for (; x; x ^= x & -x) {
      s = fun(s, val[x]);
    }
    return s;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  std::vector<std::pair<int, int>> add(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> add[i].first >> add[i].second;
    --add[i].first, --add[i].second;
  }

  auto bfs = [&](int s) {
    std::vector<int> dis(n, n);
    dis[s] = 0;
    std::vector<int> Q;
    Q.push_back(s);
    for (int i = 0; i < (int)Q.size(); ++i) {
      int u = Q[i];
      for (int v : E[u]) {
        if (dis[v] == n) {
          dis[v] = dis[u] + 1;
          Q.push_back(v);
        }
      }
    }
    return dis;
  };

  auto [x, y] = add[0];
  auto dx = bfs(x), dy = bfs(y);

  if (dx[y] <= 2) {
    std::cout << 0 << "\n";
    return 0;
  }

  std::vector<std::pair<int, int>> p;
  for (int i = 0; i < n; ++i) {
    p.emplace_back(dx[i], dy[i]);
  }
  std::sort(p.begin(), p.end());
  long long ans = 1ll * n * n;
  fenwick_tree<int> T(n);
  for (int i = n - 1, j = n - 1; i >= 0; i = j) {
    while (j >= 0 && p[i] == p[j]) {
      T.modify(p[i].second, 1);
      --j;
    }
    ans -= 1ll * (i - j) * (n - j - 1 - T.query(p[i].second));
  }
  std::cout << ans << "\n";
}
