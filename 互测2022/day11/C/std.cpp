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

using mint = modint<1000000007>;

namespace MTT {

struct complex {
  double x, y;

  complex() : x(), y() {}

  complex(double x) : x(x), y() {}

  complex(double x, double y) : x(x), y(y) {}

  complex operator+(const complex &rhs) const {
    return complex(x + rhs.x, y + rhs.y);
  }

  complex operator-(const complex &rhs) const {
    return complex(x - rhs.x, y - rhs.y);
  }

  complex operator*(const complex &rhs) const {
    return complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
  }
};

using poly = std::vector<mint>;

const int MAX_LEN = 1 << 18;
const double pi = acos(-1);

complex omega[MAX_LEN];

void init() {
  for (int m = 1; m < MAX_LEN; m <<= 1) {
    for (int i = 0; i < m; ++i) {
      omega[m + i] = {cos(pi / m * i), sin(pi / m * i)};
    }
  }
}

int enlarge(int n) {
  int res = 1;
  while (res < n) {
    res <<= 1;
  }
  return res;
}

std::vector<int> rev;

void init_rev(int n) {
  int k = 0;
  while ((1 << k) < n) {
    ++k;
  }
  rev.resize(n), rev[0] = 0, --k;
  for (int i = 1; i < n; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
  }
}

void DFT(std::vector<complex> &f, int n) {
  f.resize(n);
  static complex F[MAX_LEN];
  for (int i = 0; i < n; ++i) {
    F[rev[i]] = f[i];
  }
  for (int m = 1; m < n; m <<= 1) {
    for (int p = 0; p < n; p += m << 1) {
      complex *W = omega + m;
      complex *F0 = F + p, *F1 = F0 + m;
      for (int i = 0; i < m; ++i, ++W, ++F0, ++F1) {
        complex t = (*F1) * (*W);
        *F1 = *F0 - t, *F0 = *F0 + t;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    f[i] = F[i];
  }
}

void IDFT(std::vector<complex> &f, int n) {
  DFT(f, n), std::reverse(f.begin() + 1, f.end());
  for (int i = 0; i < n; ++i) {
    f[i] = f[i] * (complex){1.0 / n, 0};
  }
}

poly multiply(const poly &f, const poly &g) {
  int fn = f.size(), gn = g.size(), tn = fn + gn - 1;
  std::vector<complex> fa(fn), fb(fn), ga(gn), gb(gn);
  for (int i = 0; i < fn; ++i) {
    fa[i] = f[i].val() >> 16;
    fb[i] = f[i].val() & 65535;
  }
  for (int i = 0; i < gn; ++i) {
    ga[i] = g[i].val() >> 16;
    gb[i] = g[i].val() & 65535;
  }
  int n = enlarge(tn);
  init_rev(n);
  DFT(fa, n), DFT(fb, n), DFT(ga, n), DFT(gb, n);
  std::vector<complex> a(n), b(n), c(n);
  for (int i = 0; i < n; ++i) {
    a[i] = fa[i] * ga[i];
    b[i] = fa[i] * gb[i] + fb[i] * ga[i];
    c[i] = fb[i] * gb[i];
  }
  IDFT(a, n), IDFT(b, n), IDFT(c, n);
  poly ans(tn);
  for (int i = 0; i < tn; ++i) {
    long long A = a[i].x + 0.5, B = b[i].x + 0.5, C = c[i].x + 0.5;
    ans[i] = mint(1ll << 32) * A + mint(1ll << 16) * B + C;
  }
  return ans;
}

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<mint> f(n + 1);
  f[0] = 1;
  for (int i = 0; i < n * m; ++i) {
    mint v;
    std::cin >> v;
    for (int j = n; j >= 1; --j) {
      f[j] += f[j - 1] * v;
    }
  }
  std::vector<mint> fac(n * m + 1), ifac(n * m + 1);
  fac[0] = 1;
  for (int i = 1; i <= n * m; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  ifac[n * m] = fac[n * m].inv();
  for (int i = n * m; i >= 1; --i) {
    ifac[i - 1] = ifac[i] * i;
  }
  MTT::init();
  MTT::poly g(n + 1), h(n + 1);
  for (int i = 1; i <= n; ++i) {
    g[i] = ifac[i * m - 1];
  }
  mint ans = 0;
  h[0] = 1;
  for (int k = 1; k <= n; ++k) {
    h = MTT::multiply(h, g);
    h.resize(n + 1);
    ans += h[n] * fac[n * m - k] * f[k];
  }
  std::cout << ans << "\n";
}
