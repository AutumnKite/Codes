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
  int n, lg;
  std::vector<int> Lg;
  std::vector<std::vector<int>> E;
  std::vector<int> fa, dep, len, son, top;
  std::vector<std::vector<int>> up, down;
  std::vector<std::vector<int>> anc;

  void dfs1(int u) {
    anc[u][0] = fa[u];
    for (int i = 1; i < lg && anc[u][i - 1] != -1; ++i) {
      anc[u][i] = anc[anc[u][i - 1]][i - 1];
    }
    son[u] = -1;
    for (int v : E[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      if (son[u] == -1 || len[v] > len[son[u]]) {
        son[u] = v;
      }
    }
    len[u] = son[u] == -1 ? 0 : len[son[u]] + 1;
  }

  void dfs2(int u, int tp) {
    down[tp].push_back(u);
    top[u] = tp;
    if (son[u] != -1) {
      dfs2(son[u], tp);
    }
    for (int v : E[u]) {
      if (v != son[u]) {
        dfs2(v, v);
        up[v].reserve(len[v]);
        for (int i = 0, x = u; i < len[v] && x != -1; x = fa[x], ++i) {
          up[v].push_back(x);
        }
      }
    }
  }

public:
  tree(std::vector<int> t_fa)
  : n(t_fa.size()), lg(std::__lg(n) + 1), Lg(n + 1), E(n),
    fa(t_fa), dep(n), len(n), son(n), top(n), up(n), down(n),
    anc(n, std::vector<int>(lg, -1)) {
    Lg[1] = 0;
    for (int i = 2; i < n; ++i) {
      Lg[i] = Lg[i >> 1] + 1;
    }
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
    if (k == 0) {
      return u;
    }
    u = anc[u][Lg[k]];
    k ^= 1 << Lg[k];
    if (dep[u] - dep[top[u]] >= k) {
      return down[top[u]][dep[u] - dep[top[u]] - k];
    } else {
      return up[top[u]][k - (dep[u] - dep[top[u]]) - 1];
    }
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

  int B = 1.2 * sqrt(n) + 1, C = (n - 1) / B + 1;
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

  std::vector<mint> dv(n);
  std::vector<int> tmp;
  int last = 0;
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    l ^= last, r ^= last;
    --l, --r;
    int x = r;
    r = std::min(r, p[l]);
    int bel = x / B, bound = bel * B;
    mint ans = pre[bel][std::min(r + 1, bound)]
             - pre[bel][std::min(l, bound)];
    for (int i = std::max(l, bound); i <= x; ++i) {
      int d = T.depth(i) - T.depth(l);
      int u = !d ? i : T.query(i, d - 1);
      if (fa[u] >= l) {
        u = fa[u];
      }
      dv[u] += a[i];
      tmp.push_back(u);
    }
    for (int x : tmp) {
      if (dv[x].val()) {
        ans += (x < bound ? sum[bel][x] + sum[bel][x] + dv[x] : dv[x]) * dv[x];
        dv[x] = mint();
      }
    }
    tmp.clear();
    std::cout << ans << "\n";
    last = ans.val();
  }
}
