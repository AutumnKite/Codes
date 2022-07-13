#include <bits/stdc++.h>

template<unsigned id>
class dynamic_modint {
  using mint = dynamic_modint<id>;

protected:
  static unsigned P;

  unsigned v;

public:
  dynamic_modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  dynamic_modint(T t_v) : v() {
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
  dynamic_modint(T t_v) : v() {
    v = t_v % P;
  }

  unsigned val() const {
    return v;
  }

  static unsigned mod() {
    return P;
  }

  static void set_mod(unsigned nP) {
    P = nP;
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

template<unsigned id>
unsigned dynamic_modint<id>::P;

constexpr unsigned pow_mod_constexpr(unsigned a, unsigned b, unsigned P) {
  unsigned s = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      s = static_cast<unsigned long long>(s) * a % P;
    }
    a = static_cast<unsigned long long>(a) * a % P;
  }
  return s;
}

constexpr unsigned primitive_root(unsigned n) {
  if (n == 998244353) {
    return 3;
  }
  unsigned x = n - 1;
  unsigned cnt = 0;
  unsigned div[20] = {};
  for (unsigned i = 2; i <= x / i; ++i) {
    if (x % i == 0) {
      div[cnt++] = i;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x > 1) {
    div[cnt++] = x;
  }
  unsigned g = 1;
  while (1) {
    bool ok = true;
    for (unsigned i = 0; i < cnt; ++i) {
      if (pow_mod_constexpr(g, (n - 1) / div[i], n) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) {
      return g;
    }
    ++g;
  }
  return 0;
}

using mint = dynamic_modint<0>;

namespace MTTPoly {
  struct Complex {
    double x, y;

    Complex operator + (const Complex &rhs) const {
      return {x + rhs.x, y + rhs.y};
    }

    Complex operator - (const Complex &rhs) const {
      return {x - rhs.x, y - rhs.y};
    }

    Complex operator * (const Complex & rhs) const {
      return {x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x};
    }
  };

  const int MAX_LEN = 1 << 20;
  const double pi = acos(-1);

  typedef std::vector<int> poly;

  Complex omega[MAX_LEN];

  void Init() {
    for (int m = 1; m < MAX_LEN; m <<= 1) {
      for (int i = 0; i < m; ++i) {
        omega[m + i] = {cos(pi / m * i), sin(pi / m * i)};
      }
    }
  }

  int get(int _n) {
    int n = 1;
    while (n < _n) {
      n <<= 1;
    }
    return n;
  }

  std::vector<int> rev;

  void init(int n) {
    int k = 0;
    while ((1 << k) < n) {
      ++k;
    }
    rev.resize(n), rev[0] = 0, --k;
    for (int i = 1; i < n; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
    }
  }

  void DFT(std::vector<Complex> &f, int n) {
    f.resize(n);
    static Complex F[MAX_LEN];
    for (int i = 0; i < n; ++i) {
      F[rev[i]] = f[i];
    }
    for (int m = 1; m < n; m <<= 1) {
      for (int p = 0; p < n; p += m << 1) {
        Complex *W = omega + m;
        Complex *F0 = F + p, *F1 = F0 + m;
        for (int i = 0; i < m; ++i, ++W, ++F0, ++F1) {
          Complex t = (*F1) * (*W);
          *F1 = *F0 - t, *F0 = *F0 + t;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      f[i] = F[i];
    }
  }

  void IDFT(std::vector<Complex> &f, int n) {
    DFT(f, n), std::reverse(f.begin() + 1, f.end());
    for (int i = 0; i < n; ++i) {
      f[i] = f[i] * (Complex){1.0 / n, 0};
    }
  }

  poly Mul(const poly &f, const poly &g, int P) {
    int fn = f.size(), gn = g.size(), _n = fn + gn - 1;
    std::vector<Complex> fa(fn), fb(fn), ga(gn), gb(gn);
    for (int i = 0; i < fn; ++i) {
      fa[i].x = f[i] >> 15, fa[i].y = 0;
      fb[i].x = f[i] & 32767, fb[i].y = 0;
    }
    for (int i = 0; i < gn; ++i) {
      ga[i].x = g[i] >> 15, ga[i].y = 0;
      gb[i].x = g[i] & 32767, gb[i].y = 0;
    }
    int n = get(_n);
    init(n), DFT(fa, n), DFT(fb, n), DFT(ga, n), DFT(gb, n);
    std::vector<Complex> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
      a[i] = fa[i] * ga[i];
      b[i] = fa[i] * gb[i] + fb[i] * ga[i];
      c[i] = fb[i] * gb[i];
    }
    IDFT(a, n), IDFT(b, n), IDFT(c, n);
    poly ans(_n);
    for (int i = 0; i < _n; ++i) {
      long long A = a[i].x + 0.5, B = b[i].x + 0.5, C = c[i].x + 0.5;
      A %= P, B %= P, C %= P;
      ans[i] = ((1 << 30) * A + (1 << 15) * B + C) % P;
      ans[i] = (P + ans[i]) % P;
    }
    return ans;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, mod;
  long long m;
  std::cin >> n >> mod >> m;
  mint::set_mod(mod);
  std::vector<mint> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    a[i] *= mint(n).pow(m / 2);
  }
  if (m & 2) {
    std::reverse(a.begin() + 1, a.end());
  }
  m &= 1;
  if (m == 0) {
    for (int i = 0; i < n; ++i) {
      std::cout << a[i] << " \n"[i == n - 1];
    }
    return 0;
  }

  mint w = mint(primitive_root(mod)).pow((mod - 1) / n);
  std::vector<mint> pw(2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    pw[i] = w.pow(1ll * i * (i - 1) / 2);
  }
  MTTPoly::poly f(n), g(2 * n);
  for (int i = 0; i < n; ++i) {
    f[i] = (a[i] * pw[i].inv()).val();
  }
  for (int i = 0; i < 2 * n; ++i) {
    g[i] = pw[i].val();
  }
  std::reverse(f.begin(), f.end());
  MTTPoly::Init();
  auto res = MTTPoly::Mul(f, g, mod);
  for (int i = 0; i < n; ++i) {
    std::cout << res[i + n - 1] * pw[i].inv() << " \n"[i == n - 1];
  }
}
