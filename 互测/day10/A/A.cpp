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

  std::vector<std::vector<int>> id(n + 1, std::vector<int>(n + 1, -1));
  int tot = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; i + j <= n; ++j) {
      id[i][j] = tot++;
    }
  }

  std::vector<mint> f(tot);
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    ++f[id[a][b]];
  }

  auto mul = [&](std::vector<mint> &f, mint w) {
    mint w2 = w * w;
    for (int x = n; x >= 0; --x) {
      for (int y = n - x; y >= 0; --y) {
        if (x) {
          f[id[x][y]] += w * f[id[x - 1][y]];
        }
        if (y) {
          f[id[x][y]] += w2 * f[id[x][y - 1]];
        }
      }
    }
    for (int x = 0; x <= n; ++x) {
      for (int y = 0; x + y <= n; ++y) {
        if (x) {
          f[id[x][y]] -= f[id[x - 1][y]];
        }
        if (y) {
          f[id[x][y]] -= f[id[x][y - 1]];
        }
      }
    }
  };

  std::vector<std::vector<mint>> H(tot, std::vector<mint>(tot));
  for (int x = 0; x <= n; ++x) {
    for (int y = 0; x + y <= n; ++y) {
      H[id[0][0]][id[x][y]] = C[n][x] * C[n - x][y];
    }
  }
  for (int i = 1; i <= n; ++i) {
    H[id[i][0]] = H[id[i - 1][0]];
    mul(H[id[i][0]], omega);
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 1; i + j <= n; ++j) {
      H[id[i][j]] = H[id[i][j - 1]];
      mul(H[id[i][j]], omega * omega);
    }
  }

  auto FWT = [&](const std::vector<mint> &f) {
    std::vector<mint> res(tot);
    for (int i = 0; i < tot; ++i) {
      for (int x = 0; x <= n; ++x) {
        for (int y = 0; x + y <= n; ++y) {
          res[i] += f[id[x][y]] * H[i][id[x][y]];
        }
      }
    }
    return res;
  };

  f = FWT(f);

  for (int i = 0; i < tot; ++i) {
    f[i] = f[i].pow(k);
  }

  auto IFWT = [&](const std::vector<mint> &f) {
    std::vector<mint> res(tot);
    for (int i = 0; i < tot; ++i) {
      for (int x = 0; x <= n; ++x) {
        for (int y = 0; x + y <= n; ++y) {
          res[i] += f[id[x][y]] * H[i][id[y][x]];
        }
      }
    }
    return res;
  };

  f = IFWT(f);

  mint inv = mint(3).pow(n).inv();
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; i + j <= n; ++j) {
      std::cout << f[id[i][j]] * C[n][i] * C[n - i][j] * inv;
      std::cout << " \n"[i + j == n];
    }
  }
}
