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

using mint = modint<1000000007>;

class tree {
  std::vector<int> a;
  int n;
  std::vector<std::vector<int>> E;
  fenwick_tree<int, std::bit_xor<int>> T;

  int idx;
  std::vector<int> fa, dep, size, son, top, dfn;

  void dfs(int u) {
    size[u] = 1;
    son[u] = -1;
    for (int v : E[u]) {
      if (v != fa[u]) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]]) {
          son[u] = v;
        }
      }
    }
  }

  void dfs(int u, int tp) {
    top[u] = tp;
    dfn[u] = idx++;
    if (son[u] != -1) {
      dfs(son[u], tp);
    }
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs(v, v);
      }
    }
  }

  int LCA(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) {
        std::swap(u, v);
      }
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }

public:
  tree(std::vector<int> t_a) : a(t_a), n(a.size()), E(n), T(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  void modify(int x, int v) {
    a[x] ^= v;
    T.modify(dfn[x], v);
    if (dfn[x] + size[x] < n) {
      T.modify(dfn[x] + size[x], v);
    }
  }

  int query(int u, int v) {
    return T.query(dfn[u] + 1) ^ T.query(dfn[v] + 1) ^ a[LCA(u, v)];
  }

  void init() {
    fa.assign(n, -1);
    dep.assign(n, 0);
    size.resize(n);
    son.resize(n);
    top.resize(n);
    dfn.resize(n);
    idx = 0;
    dfs(0);
    dfs(0, 0);
    for (int i = 0; i < n; ++i) {
      int tmp = a[i];
      a[i] = 0;
      modify(i, tmp);
    }
  }
};

void FWT(std::vector<mint> &f) {
  int n = f.size();
  for (int m = 1; m < n; m <<= 1) {
    for (int i = 0; i < n; i += m << 1) {
      for (int j = 0; j < m; ++j) {
        mint tmp = f[i + j] - f[m + i + j];
        f[i + j] += f[m + i + j];
        f[m + i + j] = tmp;
      }
    }
  }
}

void IFWT(std::vector<mint> &f) {
  FWT(f);
  mint inv = mint(2).pow(std::__lg(f.size())).inv();
  for (auto &x : f) {
    x *= inv;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, c, n;
  std::cin >> m >> c >> n;
  std::vector<mint> ans(1 << c);
  for (int i = 0; i < c; ++i) {
    std::cin >> ans[1 << i];
  }
  std::vector<mint> cnt(1 << c);
  for (int i = 0; i < m; ++i) {
    int mask = 0;
    int k;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      int x;
      std::cin >> x;
      mask |= 1 << x;
    }
    ++cnt[mask];
  }
  ans[0] = 0;
  for (int S = 1; S < (1 << c); ++S) {
    ans[S] = std::gcd(ans[S & (S - 1)].val(), ans[S & -S].val());
  }
  FWT(cnt);
  IFWT(cnt);
  FWT(cnt);
  FWT(ans);
  for (int S = 0; S < (1 << c); ++S) {
    ans[S] *= cnt[S];
  }
  IFWT(ans);
  
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    a[i] = 1 << a[i];
  }
  tree T(a);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    T.add_edge(u, v);
  }
  T.init();
  int now = 0;
  for (int k = 0; k < m; ++k) {
    int u, v, w, c;
    std::cin >> u >> v >> w >> c;
    now ^= T.query(u, v);
    std::cout << ans[now] << " \n"[k == m - 1];
    T.modify(w, a[w] ^ (1 << c));
    a[w] = 1 << c;
  }
}
