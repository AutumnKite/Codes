#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P);

  using mint = modint<P>;

protected:
  unsigned v;

public:
  constexpr modint() : v() {}

  template<typename T, 
           typename std::enable_if<
                    std::is_signed<T>::value
                    && std::is_integral<T>::value,
                    bool>::type = true>
  constexpr modint(T _v) : v() {
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
  constexpr modint(T _v) : v() {
    v = _v % P;
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
    v == 0 ? v = P - 1 : --v;
    return *this;
  }

  constexpr mint operator--(int) {
    mint tmp = *this;
    v == 0 ? v = P - 1 : --v;
    return tmp;
  }

  constexpr mint operator-() const {
    mint res;
    res.v = v == 0 ? 0 : P - v;
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

using mint = modint<1000000009>;

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

constexpr mint omega = mint(primitive_root(mint::mod()))
                       .pow((mint::mod() - 1) / 3);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  long long k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<mint>> C(n + 1, std::vector<mint>(n + 1));
  for (int i = 0; i <= n; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }

  std::vector<std::vector<mint>> g(n + 1, std::vector<mint>(n + 1));
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    g[a][b] += C[n][a] * C[n - a][b];
  }
  std::vector<std::vector<mint>> f(n + 1, std::vector<mint>(n + 1));
  f[0][0] = 1;

  auto calc = [&](mint w) {
    std::vector<std::vector<std::vector<mint>>>
    f(n + 1, std::vector<std::vector<mint>>(n + 1, std::vector<mint>(n + 1)));
    f[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
      f[i] = f[i - 1];
      for (int x = 1; x <= n; ++x) {
        for (int y = 0; y <= n; ++y) {
          f[i][x][y] += f[i - 1][x - 1][y] * w;
        }
      }
      for (int x = 0; x <= n; ++x) {
        for (int y = 1; y <= n; ++y) {
          f[i][x][y] += f[i - 1][x][y - 1] * w;
        }
      }
    }
    return f;
  };

  std::array pw = {calc(1), calc(omega), calc(omega * omega)};
  
  auto FWT = [&](const auto &f) {
    std::vector<std::vector<mint>> res(n + 1, std::vector<mint>(n + 1));
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; i + j <= n; ++j) {
        for (int x = 0; x <= n; ++x) {
          for (int y = 0; x + y <= n; ++y) {
            res[i][j] += f[x][y] * (pw[0][n - i - j][x][y]
                                    + pw[1][i][x][y]
                                    + pw[2][j][x][y]);
          }
        }
      }
    }
    return res;
  };

  f = FWT(f), g = FWT(g);
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; i + j <= n; ++j) {
      f[i][j] *= g[i][j].pow(k);
    }
  }
}
