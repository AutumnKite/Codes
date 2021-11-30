#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P);

  using mint = modint<P>;

protected:
  unsigned v;

public:
  modint() : v() {}

  template<typename T, 
           typename std::enable_if<
                    std::is_signed<T>::value
                    && std::is_integral<T>::value,
                    bool>::type = true>
  modint(T _v) {
    long long tmp = _v % static_cast<long long>(P);
    if (tmp < 0) {
      tmp += P;
    }
    v = tmp;
  }

  template<typename T, 
           typename std::enable_if<
                    std::is_unsigned<T>::value
                    && std::is_integral<T>::value,
                    bool>::type = true>
  modint(T _v) {
    v = _v % P;
  }

  unsigned val() const {
    return v;
  }

  static constexpr unsigned mod() {
    return P;
  }

  static mint raw(unsigned v) {
    mint res;
    res.v = v;
    return res;
  }

  mint &operator+=(const mint &rhs) {
    v < P - rhs.v ? v += rhs.v : v -= P - rhs.v;
    return *this;
  }

  mint &operator++() {
    v + 1 < P ? ++v : v = 0;
    return *this;
  }

  mint operator++(int) {
    mint tmp = *this;
    v + 1 < P ? ++v : v = 0;
    return tmp;
  }

  mint &operator-=(const mint &rhs) {
    v < rhs.v ? v += P - rhs.v : v -= rhs.v;
    return *this;
  }

  mint &operator--() {
    v == 0 ? v = P - 1 : --v;
    return *this;
  }

  mint operator--(int) {
    mint tmp = *this;
    v == 0 ? v = P - 1 : --v;
    return tmp;
  }

  mint operator-() const {
    mint res;
    res.v = v == 0 ? 0 : P - v;
    return res;
  }

  mint &operator*=(const mint &rhs) {
    v = static_cast<unsigned long long>(v) * rhs.v % P;
    return *this;
  }

  mint pow(unsigned long long b) const {
    mint a(*this), s(1);
    for (; b; b >>= 1) {
      if (b & 1) {
        s *= a;
      }
      a *= a;
    }
    return s;
  }

  mint inv() const {
    return pow(P - 2);
  }

  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }

  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }

  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }

  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs.v == rhs.v;
  }

  friend bool operator!=(const mint &lhs, const mint &rhs) {
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
  std::vector<int> fa, dep, size, son, top, dfn, nd;

  void dfs1(int u) {
    size[u] = 1;
    son[u] = -1;
    for (int v : E[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      size[u] += size[v];
      if (son[u] == -1 || size[v] > size[son[u]]) {
        son[u] = v;
      }
    }
  }

  void dfs2(int u, int tp) {
    dfn[u] = nd.size();
    nd.push_back(u);
    top[u] = tp;
    if (son[u] == -1) {
      dfs2(son[u], tp);
    }
    for (int v : E[u]) {
      if (v != son[u]) {
        dfs2(v, v);
      }
    }
  }

public:
  tree(std::vector<int> t_fa)
  : n(t_fa.size()), E(n), fa(t_fa), dep(n), size(n), son(n), top(n), dfn(n) {
    for (int i = 1; i < n; ++i) {
      E[fa[i]].push_back(i);
    }
    dfs1(0);
    dfs2(0, 0);
  }

  int depth(int u) const {
    return dep[u];
  }

  int query(int u, int k) const {
    int st = dep[u];
    while (st - dep[u] < k) {
      if (st - dep[top[u]] >= k) {
        return nd[dfn[u] - (k - (st - dep[u]))];
      }
      u = fa[top[u]];
    }
    return u;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  std::vector<mint> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<int> fa(n, -1);
  for (int i = 1; i < n; ++i) {
    std::cin >> fa[i];
    --fa[i];
  }
  std::vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    p[i] = std::lower_bound(fa.begin(), fa.end(), i) - fa.begin() - 1;
  }

  tree T(fa);

  int B = sqrt(n) + 1, C = (n - 1) / B + 1;
  std::vector<std::vector<mint>> sum(C), pre(C);
  for (int k = 0; k < C; ++k) {
    sum[k].resize(k * B);
    for (int i = k * B - 1; i >= 0; --i) {
      sum[k][i] += a[i];
      if (i) {
        sum[k][fa[i]] += sum[k][i];
      }
    }
    pre[k].resize(k * B + 1);
    for (int i = 0; i < k * B; ++i) {
      pre[k][i + 1] = pre[k][i] + sum[k][i] * sum[k][i];
    }
  }

  int last = 0;
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    l ^= last, r ^= last;
    --l, --r;
    int x = r;
    r = std::min(r, p[l]);
    mint ans = pre[x / B][std::min(r + 1, x / B * B)]
             - pre[x / B][std::min(l, x / B * B)];
    for (int i = std::max(l, x / B * B); i <= x; ++i) {
      int d = T.depth(i) - T.depth(l);
      int u = !d ? i : T.query(i, d - 1);
      if (fa[u] >= l) {
        u = fa[u];
      }
    }
  }
}
