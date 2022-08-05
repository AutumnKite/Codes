#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P, "P must be a positive integer");

  using mint = modint<P>;

protected:
  unsigned v;

public:
  modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  modint(T t_v) : v() {
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
  modint(T t_v) : v() {
    v = t_v % P;
  }

  unsigned val() const {
    return v;
  }

  static unsigned mod() {
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
    v ? --v : v = P - 1;
    return *this;
  }
  
  mint operator--(int) {
    mint tmp = *this;
    v ? --v : v = P - 1;
    return tmp;
  }

  mint operator-() const {
    mint res;
    res.v = v ? P - v : 0;
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

template<unsigned P, unsigned L>
class modpoly {
  using mint = modint<P>;
  using poly = modpoly<P, L>;

public:
  typedef std::size_t size_type;

  static constexpr unsigned root = 3;

protected:
  struct initializer {
    static constexpr size_type N = static_cast<size_type>(1) << L;

    mint omega[N], inv[N + 1];

    initializer() {
      for (size_type m = 1; m < N; m <<= 1) {
        mint w = mint(root).pow((P - 1) / (m << 1));
        omega[m] = 1;
        for (size_type i = 1; i < m; ++i) {
          omega[m + i] = omega[m + i - 1] * w;
        }
      }

      inv[1] = 1;
      for (size_type i = 2; i <= N; ++i) {
        inv[i] = -mint(static_cast<unsigned>(P / i)) * inv[P % i];
      }
    }

    std::vector<size_type> rev;

    void build_rev(size_type n) {
      if (n == rev.size()) {
        return;
      }
      size_type k = 0;
      while ((static_cast<size_type>(1) << k) < n) {
        ++k;
      }
      rev.resize(n);
      rev[0] = 0;
      for (size_type i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
      }
    }
  };
  
  static initializer init;

  static const unsigned DFT_mod_cnt = 
    std::numeric_limits<unsigned long long>::max()
      / (static_cast<unsigned long long>(P) * P) - 1;
  static constexpr size_type EXP_BLOCKS = 16;
  static constexpr size_type npos = -1;

  std::vector<mint> f;

  static size_type enlarge_to_pow2(size_type n) {
    size_type res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

public:
  modpoly() {}

  modpoly(size_type n) : f(n) {}

  modpoly(size_type n, const mint &v) : f(n, v) {}

  modpoly(const std::vector<mint> &t_f) : f(t_f) {}

  modpoly(std::vector<mint> &&t_f) : f(std::move(t_f)) {}

  modpoly(const mint &v) : f(1, v) {}

  modpoly(std::initializer_list<mint> l) : f(l) {}

  template<typename Iter,
           typename = typename std::enable_if<std::is_convertible<
               typename std::iterator_traits<Iter>::iterator_category,
               std::input_iterator_tag>::value>::type>
  modpoly(Iter first, Iter last) : f(first, last) {}

  const std::vector<mint> &vec() const {
    return f;
  }

  std::vector<mint> &vec() {
    return f;
  }

  std::vector<mint> rvec() {
    return std::move(f);
  }

  bool empty() const {
    return f.empty();
  }

  size_type size() const {
    return f.size();
  }

  typename std::vector<mint>::reference operator[](size_type x) {
    return f[x];
  }

  typename std::vector<mint>::const_reference operator[](size_type x) const {
    return f[x];
  }

  void resize(size_type t_n) {
    f.resize(t_n);
  }

  bool operator<(const poly &rhs) const {
    return f.size() < rhs.f.size();
  }

  bool operator>(const poly &rhs) const {
    return f.size() > rhs.f.size();
  }

  bool operator==(const poly &rhs) const {
    return f == rhs.f;
  }

  void DFT(size_type n) {
    init.build_rev(n);
    f.resize(n);
    static unsigned long long F[initializer::N];
    for (size_type i = 0; i < n; ++i) {
      F[init.rev[i]] = f[i].val();
    }
    for (size_type m = 1; m < n; m <<= 1) {
      if (m & (static_cast<size_type>(1) << DFT_mod_cnt)) {
        for (size_type i = 0; i < n; ++i) {
          F[i] %= P;
        }
      }
      for (size_type p = 0; p < n; p += m << 1) {
        mint *W = init.omega + m;
        unsigned long long *F0 = F + p, *F1 = F + p + m;
        for (size_type i = 0; i < m; ++i, ++W, ++F0, ++F1) {
          unsigned t = (*F1) * W->val() % P;
          *F1 = *F0 + P - t, *F0 += t;
        }
      }
    }
    for (size_type i = 0; i < n; ++i) {
      f[i] = F[i];
    }
  }

  void IDFT(size_type n) {
    DFT(n);
    std::reverse(f.begin() + 1, f.end());
    mint t = init.inv[n];
    for (size_type i = 0; i < n; ++i) {
      f[i] *= t;
    }
  }

  void mul_in(poly &b, size_type t_n = npos) {
    poly &a = *this;
    if (a.empty() || b.empty() || !t_n) {
      f.clear();
      return;
    }
    t_n = std::min(t_n, a.size() + b.size() - 1);
    if (a.size() <= 32 || b.size() <= 32) {
      std::vector<mint> res(a.size() + b.size() - 1);
      for (size_type i = 0; i < a.size(); ++i) {
        for (size_type j = 0; j < b.size(); ++j) {
          res[i + j] += a.f[i] * b.f[j];
        }
      }
      res.resize(t_n);
      f.swap(res);
      return;
    }
    size_type n = enlarge_to_pow2(t_n);
    a.DFT(n), b.DFT(n);
    for (size_type i = 0; i < n; ++i) {
      a[i] *= b[i];
    }
    a.IDFT(n);
    a.vec().resize(t_n);
  }

  friend poly mul(poly a, poly b, size_type t_n = npos) {
    a.mul_in(b, t_n);
    return a;
  }

  poly &operator+=(const poly &rhs) {
    if (rhs.size() > f.size()) {
      f.resize(rhs.size());
    }
    for (size_type i = 0; i < rhs.size(); ++i) {
      f[i] += rhs[i];
    }
    return *this;
  }

  poly &operator-=(const poly &rhs) {
    if (rhs.size() > f.size()) {
      f.resize(rhs.size());
    }
    for (size_type i = 0; i < rhs.size(); ++i) {
      f[i] -= rhs[i];
    }
    return *this;
  }

  poly &operator*=(const poly &rhs) {
    poly tmp(rhs);
    mul_in(tmp);
    return *this;
  }

  poly &operator*=(const mint &rhs) {
    for (size_type i = 0; i < f.size(); ++i) {
      f[i] *= rhs;
    }
    return *this;
  }

  friend poly operator+(const poly &lhs, const poly &rhs) {
    return poly(lhs) += rhs;
  }

  friend poly operator-(const poly &lhs, const poly &rhs) {
    return poly(lhs) -= rhs;
  }

  friend poly operator*(const poly &lhs, const poly &rhs) {
    return mul(lhs, rhs);
  }

  friend poly operator*(const poly &lhs, const mint &rhs) {
    return poly(lhs) *= rhs;
  }

  poly inv(size_type t_n = npos) const {
    if (t_n == npos) {
      t_n = f.size();
    }
    size_type n = enlarge_to_pow2(t_n);
    poly a(*this), res(1);
    a.resize(n);
    res[0] = a[0].inv();
    for (size_type m = 2; m <= n; m <<= 1) {
      size_type l = m << 1;
      poly tmp(a.f.begin(), a.f.begin() + m);
      tmp.DFT(l);
      res.DFT(l);
      for (size_type i = 0; i < l; ++i) {
        res[i] += res[i] - tmp[i] * res[i] * res[i];
      }
      res.IDFT(l);
      res.resize(m);
    }
    res.resize(t_n);
    return res;
  }

  static void exp_solve(poly &g, const poly &f, size_type l, size_type r) {
    if (r - l <= 64) {
      for (size_type i = l == 0 ? 1 : l; i < r; ++i) {
        for (size_type j = l; j < i; ++j) {
          g[i] += g[j] * f[i - j];
        }
        g[i] *= init.inv[i];
      }
      return;
    }
    size_type len = (r - l) / EXP_BLOCKS;
    init.build_rev(len << 1);
    poly ta[EXP_BLOCKS], tb[EXP_BLOCKS];
    for (size_type i = 1; i < EXP_BLOCKS; ++i) {
      ta[i] = poly(f.f.begin() + (i - 1) * len, f.f.begin() + (i + 1) * len);
      ta[i].DFT(len << 1);
    }
    for (size_type i = 0; i < EXP_BLOCKS; ++i) {
      tb[i].resize(len << 1);
    }
    for (size_type i = 0; i < EXP_BLOCKS; ++i) {
      size_type nl = l + i * len, nr = nl + len;
      if (i) {
        tb[i].IDFT(len << 1);
        for (size_type j = nl; j < nr; ++j) {
          g[j] += tb[i][j - nl + len];
        }
      }
      exp_solve(g, f, nl, nr);
      if (i + 1 < EXP_BLOCKS) {
        tb[i] = poly(g.f.begin() + nl, g.f.begin() + nr);
        init.build_rev(len << 1);
        tb[i].DFT(len << 1);
        for (size_type j = i + 1; j < EXP_BLOCKS; ++j) {
          for (size_type k = 0; k < (len << 1); ++k) {
            tb[j][k] += tb[i][k] * ta[j - i][k];
          }
        }
      }
    }
  }

  poly exp(size_type t_n = npos) const {
    if (t_n == npos) {
      t_n = f.size();
    }
    poly f(*this);
    for (size_type i = 0; i < f.size(); ++i) {
      f[i] *= i;
    }
    size_type n = enlarge_to_pow2(t_n);
    f.resize(n);
    poly g(n);
    g[0] = 1;
    exp_solve(g, f, 0, n);
    g.resize(t_n);
    return g;
  }
};

template<unsigned P, unsigned L>
typename modpoly<P, L>::initializer modpoly<P, L>::init;

using mint = modint<998244353>;
using poly = modpoly<998244353, 19>;

class binom {
  std::vector<mint> fac, ifac;

public:
  binom(int n) : fac(n + 1), ifac(n + 1) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
      fac[i] = fac[i - 1] * i;
    }
    ifac[n] = fac[n].inv();
    for (int i = n; i >= 1; --i) {
      ifac[i - 1] = ifac[i] * i;
    }
  }

  mint operator()(int n, int m) const {
    if (m < 0 || m > n) {
      return mint();
    }
    return fac[n] * ifac[m] * ifac[n - m];
  }

  mint fact(int n) const {
    return fac[n];
  }

  mint ifact(int n) const {
    return ifac[n];
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> p[i];
      --p[i];
    }
    std::vector<bool> vis(n);
    std::vector<poly> g;
    binom C(n);
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) {
        int len = 0;
        for (int j = i; !vis[j]; j = p[j]) {
          vis[j] = true;
          ++len;
        }
        poly f(len / 2 + 1);
        f[0] = 1;
        for (int j = 1; j <= len / 2; ++j) {
          f[j] = C(len - j, j) + C(len - j - 1, j - 1);
        }
        g.emplace_back(f);
      }
    }
    std::priority_queue<std::pair<int, int>> Q;
    for (int i = 0; i < (int)g.size(); ++i) {
      Q.emplace(-(int)g[i].size(), i);
    }
    while (Q.size() > 1) {
      int u = Q.top().second;
      Q.pop();
      int v = Q.top().second;
      Q.pop();
      g[u] = g[u] * g[v];
      Q.emplace(-(int)g[u].size(), u);
    }
    auto &ans = g[Q.top().second];
    ans.resize(n + 1);
    std::cout << ans[k] << "\n";
  }
}
