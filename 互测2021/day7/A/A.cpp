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

using mint = modint<998244353>;

constexpr mint W[6][6] = {
  {1, 1, 0, -1, 0, -1},
  {0, -1, 1, 1, -1, 0},
  {0, 0, 1, -1, 1, -1},
  {1, -1, 0, 0, -1, 1},
  {1, 1, 1, 1, 1, 1},
  {1, -1, -1, 1, 1, -1}
};

constexpr mint IW[6][6] = {
  {332748118, 0, 0, 332748118, 166374059, 166374059},
  {332748118, 0, 665496235, 665496235, 166374059, 831870294},
  {0, 332748118, 332748118, 0, 166374059, 831870294},
  {0, 332748118, 665496235, 665496235, 166374059, 166374059},
  {665496235, 665496235, 332748118, 0, 166374059, 166374059},
  {665496235, 665496235, 0, 332748118, 166374059, 831870294},
};

void trans(std::vector<mint> &f, const mint W[6][6]) {
  for (std::size_t i = 1; i < f.size(); i *= 6) {
    for (std::size_t j = 0; j < f.size(); j += i * 6) {
      for (std::size_t k = j; k < j + i; ++k) {
        std::vector<mint> tmp(6);
        for (std::size_t x = 0; x < 6; ++x) {
          tmp[x] = 0;
          for (std::size_t y = 0; y < 6; ++y) {
            tmp[x] += W[x][y] * f[k + i * y];
          }
        }
        for (int x = 0; x < 6; ++x) {
          f[k + i * x] = tmp[x];
        }
      }
    }
  }
}

using matrix = std::vector<std::vector<mint>>;

matrix matrix_inv(matrix a) {
  int n = a.size();
  matrix b(n, std::vector<mint>(n));
  for (int i = 0; i < n; ++i) {
    b[i][i] = 1;
  }
  for (int i = 0; i < n; ++i) {
    int k = -1;
    for (int j = i; j < n; ++j) {
      if (a[j][i].val()) {
        k = j;
        break;
      }
    }
    if (k == -1) {
      throw std::invalid_argument("inverse not exist");
    }
    if (k != i) {
      std::swap(a[i], a[k]);
      std::swap(b[i], b[k]);
    }
    mint inv = a[i][i].inv();
    for (int j = i; j < n; ++j) {
      a[i][j] *= inv;
    }
    for (int j = 0; j < n; ++j) {
      b[i][j] *= inv;
    }
    for (int j = 0; j < n; ++j) {
      if (j != i && a[j][i].val()) {
        mint t = -a[j][i];
        for (int k = i; k < n; ++k) {
          a[j][k] += a[i][k] * t;
        }
        for (int k = 0; k < n; ++k) {
          b[j][k] += b[i][k] * t;
        }
      }
    }
  }
  return b;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m;
  std::cin >> m;
  int n = 1;
  for (int i = 0; i < m; ++i) {
    n *= 6;
  }
  std::vector<mint> f(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> f[i];
  }

  mint sum = std::accumulate(f.begin(), f.end(), mint(1));
  mint inv = sum.inv();
  for (int i = 0; i < n; ++i) {
    f[i] *= -inv;
  }
  ++f[0];
  trans(f, W);

  std::vector<int> pw3(m + 1);
  pw3[0] = 1;
  for (int i = 0; i < m; ++i) {
    pw3[i + 1] = pw3[i] * 3;
  }
  for (int x = 0; x < pw3[m]; ++x) {
    std::vector<int> c(m);
    int l = 0;
    for (int i = 0; i < m; ++i) {
      c[i] = x / pw3[i] % 3;
      l += !c[i];
    }
    std::vector<std::vector<int>> p(1 << l, std::vector<int>(1 << l));
    auto dfs = [&](auto &self, int k, int x, int y, int pos, int pw) -> void {
      if (k == m) {
        p[x][y] = pos;
        return;
      }
      if (!c[k]) {
        for (int i = 0; i < 4; ++i) {
          self(self, k + 1, x << 1 | (i >> 1), y << 1 | (i & 1),
               pos + pw * i, 6 * pw);
        }
      } else {
        self(self, k + 1, x, y, pos + pw * (3 + c[k]), 6 * pw);
      }
    };
    dfs(dfs, 0, 0, 0, 0, 1);
    matrix A(1 << l, std::vector<mint>(1 << l));
    for (int i = 0; i < (1 << l); ++i) {
      for (int j = 0; j < (1 << l); ++j) {
        A[i][j] = f[p[i][j]];
      }
    }
    try {
      A = matrix_inv(A);
    }
    catch (std::invalid_argument const&) {
      std::cout << -1 << "\n";
      return 0;
    }
    for (int i = 0; i < (1 << l); ++i) {
      for (int j = 0; j < (1 << l); ++j) {
        f[p[i][j]] = A[i][j];
      }
    }
  }

  trans(f, IW);
  unsigned ans = 0;
  for (int i = 0; i < n; ++i) {
    ans ^= (f[i] * inv).val();
  }
  std::cout << ans << "\n";
}
