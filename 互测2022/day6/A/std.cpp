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

constexpr mint inv2 = mint(2).inv();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  mint X, Y;
  int N, r, b, m;
  std::cin >> N >> X >> Y >> r >> b >> m;
  mint q = X * Y.inv(), last = mint(Y).pow(N);
  std::vector<mint> h(r + 1);
  for (int i = 0; i <= r; ++i) {
    std::cin >> h[i];
  }

  // int n = std::min(r + b, 2 * m);
  int n = N;
  std::vector<mint> fac(n + 1), ifac(n + 1);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  ifac[n] = fac[n].inv();
  for (int i = n; i >= 1; --i) {
    ifac[i - 1] = ifac[i] * i;
  }
  std::vector<mint> C(n + 1);
  C[0] = 1;
  for (int i = 1; i <= n; ++i) {
    C[i] = C[i - 1] * (n - i + 1);
  }
  for (int i = 0; i <= n; ++i) {
    C[i] *= ifac[i];
  }

  auto binom = [&](int n, int m) {
    if (m < 0 || m > n) {
      return mint();
    }
    return fac[n] * ifac[m] * ifac[n - m];
  };

  std::vector<mint> coef(m + 1);
  for (int a = b & 1; a <= r && a + b <= 2 * m; a += 2) {
    mint pw = 1, sum = 0;
    for (int p = 0; p <= N; ++p) {
      sum += binom(p, a) * binom(N - p, b) * pw;
      pw *= q;
    }
    coef[(a + b) / 2] = sum * h[a] * C[a + b].inv();
  }

  int L = (b + 1) / 2, R = std::min(m, (r + b) / 2);
  if (L > R) {
    for (int i = 0; i <= m; ++i) {
      std::cout << 0 << " \n"[i == m];
    }
    return 0;
  }
  std::vector<mint> f(m + 1);
  f[0] = 1;
  for (int k = 0; k <= m; ++k) {
    mint ans = 0;
    for (int i = L; i <= R; ++i) {
      ans += f[i] * coef[i];
    }
    std::cout << ans * last << " \n"[k == m];
    std::vector<mint> g(m + 1);
    for (int i = 0; i <= m; ++i) {
      if (i < m) {
        g[i + 1] += f[i] * (N - 2 * i) * (N - 2 * i - 1) * inv2;
      }
      if (i > 0) {
        g[i - 1] += f[i] * i * (2 * i - 1);
      }
      g[i] += f[i] * (2 * i) * (N - 2 * i);
    }
    f.swap(g);
  }
}
