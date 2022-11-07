#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P, "P must be a positive integer");

  using mint = modint<P>;

protected:
  unsigned v;

public:
  constexpr modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  constexpr modint(T t_v) : v() {
    long long tmp = t_v % static_cast<long long>(P);
    if (tmp < 0) {
      tmp += P;
    }
    v = tmp;
  }

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_unsigned<T>::value,
                                   bool>::type = true>
  constexpr modint(T t_v) : v() {
    v = t_v % P;
  }

  constexpr unsigned val() const {
    return v;
  }

  static constexpr unsigned mod() {
    return P;
  }

  static constexpr mint raw(unsigned v) {
    mint res;
    res.v = v;
    return res;
  }

  constexpr mint &operator+=(const mint &rhs) {
    v < P - rhs.v ? v += rhs.v : v -= P - rhs.v;
    return *this;
  }

  constexpr mint &operator++() {
    v + 1 < P ? ++v : v = 0;
    return *this;
  }

  constexpr mint operator++(int) {
    mint tmp = *this;
    v + 1 < P ? ++v : v = 0;
    return tmp;
  }

  constexpr mint &operator-=(const mint &rhs) {
    v < rhs.v ? v += P - rhs.v : v -= rhs.v;
    return *this;
  }

  constexpr mint &operator--() {
    v ? --v : v = P - 1;
    return *this;
  }
  
  constexpr mint operator--(int) {
    mint tmp = *this;
    v ? --v : v = P - 1;
    return tmp;
  }

  constexpr mint operator-() const {
    mint res;
    res.v = v ? P - v : 0;
    return res;
  }

  constexpr mint &operator*=(const mint &rhs) {
    v = static_cast<unsigned long long>(v) * rhs.v % P;
    return *this;
  }

  constexpr mint pow(unsigned long long b) const {
    mint a(*this), s(1);
    for (; b; b >>= 1) {
      if (b & 1) {
        s *= a;
      }
      a *= a;
    }
    return s;
  }

  constexpr mint inv() const {
    return pow(P - 2);
  }

  constexpr friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }

  constexpr friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }

  constexpr friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }

  constexpr friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs.v == rhs.v;
  }

  constexpr friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs.v != rhs.v;
  }

  friend std::istream &operator>>(std::istream &in, mint &x) {
    return in >> x.v;
  }

  friend std::ostream &operator<<(std::ostream &out, const mint &x) {
    return out << x.v;
  }
};

using mint = modint<998244353>;

class tree {
  int n;
  std::vector<std::vector<int>> E;

  int idx;
  std::vector<int> fa, dep, size, son, top, dfn;
  std::vector<mint> sum;

  void dfs1(int u) {
    for (int v : E[u]) {
      if (v != fa[u]) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v);
        sum[u] += mint(size[v]) * size[u];
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]]) {
          son[u] = v;
        }
      }
    }
    sum[u] += mint(n - size[u]) * size[u];
  }

  void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = idx++;
    if (son[u] != -1) {
      dfs2(son[u], tp);
    }
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs2(v, v);
      }
    }
  }

  int LCA(int u, int v) const {
    while (top[u] != top[v]) {
      if (dep[top[u]] > dep[top[v]]) {
        u = fa[top[u]];
      } else {
        v = fa[top[v]];
      }
    }
    return dep[u] < dep[v] ? u : v;
  }

  bool subtree(int u, int v) const {
    return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + size[u];
  }

  int next(int u, int v) const {
    if (subtree(u, v)) {
      while (top[u] != top[v] && fa[top[v]] != u) {
        v = fa[top[v]];
      }
      if (top[u] == top[v]) {
        return son[u];
      } else {
        return top[v];
      }
    } else {
      return fa[u];
    }
  }

public:
  tree(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  void init() {
    fa.assign(n, -1);
    dep.assign(n, 0);
    size.assign(n, 1);
    son.assign(n, -1);
    top.assign(n, 0);
    dfn.assign(n, 0);
    idx = 0;
    sum.assign(n, 1);
    dfs1(0);
    dfs2(0, 0);
  }

  int dis(int u, int v) const {
    return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
  }

  using chain = std::pair<int, int>;

  chain merge(chain A, chain B) const {
    std::vector<int> p{A.first, A.second, B.first, B.second};
    std::vector<std::vector<int>> d(4, std::vector<int>(4));
    int max = 0, u = 0, v = 0;
    for (int i = 0; i < 4; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        d[j][i] = d[i][j] = dis(p[i], p[j]);
        if (d[i][j] > max) {
          max = d[i][j];
          u = i, v = j;
        }
      }
    }
    for (int i = 0; i < 4; ++i) {
      if (d[i][u] + d[i][v] != d[u][v]) {
        return std::make_pair(-1, -1);
      }
    }
    return std::make_pair(p[u], p[v]);
  }

  mint calc(int u, int v) const {
    if (u == v) {
      return sum[u];
    }
    if (dfn[u] > dfn[v]) {
      std::swap(u, v);
    }
    if (subtree(u, v)) {
      return mint(n - size[next(u, v)]) * size[v];
    } else {
      return mint(size[u]) * size[v];
    }
  }

  mint calc0(int rt, int u, int v) const {
    int du = dis(rt, u), dv = dis(rt, v);
    if (du > dv) {
      std::swap(u, v);
      std::swap(du, dv);
    }
    if (dis(u, v) == dv - du) {
      return calc(next(u, v), v);
    } else {
      return calc(u, v);
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int sub;
  std::cin >> sub;
  int n, m;
  std::cin >> n >> m;
  tree T(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    T.add_edge(u, v);
  }
  T.init();
  std::vector<tree::chain> c(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> c[i].first >> c[i].second;
    --c[i].first, --c[i].second;
  }
  mint ans = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      if (c[i].first == c[j].first) {
        ans += T.calc0(c[i].first, c[i].second, c[j].second);
      } else if (c[i].first == c[j].second) {
        ans += T.calc0(c[i].first, c[i].second, c[j].first);
      } else if (c[i].second == c[j].first) {
        ans += T.calc0(c[i].second, c[i].first, c[j].second);
      } else if (c[i].second == c[j].second) {
        ans += T.calc0(c[i].second, c[i].first, c[j].first);
      } else {
        auto [u, v] = T.merge(c[i], c[j]);
        if (u != -1) {
          ans += T.calc(u, v);
        }
      }
    }
  }
  std::cout << ans * 2 + 1ll * n * (n + 1) / 2 * mint(m) << "\n";
}
