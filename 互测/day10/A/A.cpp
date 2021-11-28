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

using mint = modint<1000000009>;

using matrix = std::vector<std::vector<mint>>;

matrix mul(const matrix &A, const matrix &B) {
  matrix res(A.size(), std::vector<mint>(B[0].size()));
  for (std::size_t i = 0; i < A.size(); ++i) {
    for (std::size_t k = 0; k < B.size(); ++k) {
      for (std::size_t j = 0; j < B[0].size(); ++j) {
        res[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return res;
}

matrix qpow(matrix a, int b) {
  matrix s(a.size(), std::vector<mint>(a.size()));
  for (std::size_t i = 0; i < a.size(); ++i) {
    s[i][i] = 1;
  }
  for (; b; b >>= 1) {
    if (b & 1) {
      s = mul(s, a);
    }
    a = mul(a, a);
  }
  return s;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  long long k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<mint>> cnt(n + 1, std::vector<mint>(n + 1));
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    ++cnt[a][b];
  }

  std::vector<std::vector<mint>> binom(n + 1, std::vector<mint>(n + 1));
  for (int i = 0; i <= n; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
    }
  }

  std::vector<std::vector<int>> id(n + 1, std::vector<int>(n + 1, -1));
  int tot = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; i + j <= n; ++j) {
      id[i][j] = tot++;
    }
  }
  std::vector<std::vector<mint>> coef(tot, std::vector<mint>(tot));

  for (int a = 0; a <= n; ++a) {
    for (int b = 0; a + b <= n; ++b) {
      if (cnt[a][b].val()) {
        for (int a0 = 0; a0 <= a; ++a0) {
          for (int a1 = 0; a0 + a1 <= a; ++a1) {
            int a2 = a - a0 - a1;
            for (int b0 = 0; b0 <= b; ++b0) {
              for (int b1 = 0; b0 + b1 <= b; ++b1) {
                int b2 = b - b0 - b1;
                for (int c0 = a0 + b0; c0 <= n - a2 - b2; ++c0) {
                  for (int c1 = a1 + b1; c0 + c1 <= n - a2 - b2; ++c1) {
                    int c2 = n - c0 - c1;
                    int nc1 = a0 + b2 + c1 - a1 - b1;
                    int nc2 = b0 + a1 + c2 - a2 - b2;
                    coef[id[c1][c2]][id[nc1][nc2]] += cnt[a][b]
                      * binom[c0][a0] * binom[c0 - a0][b0]
                      * binom[c1][a1] * binom[c1 - a1][b1]
                      * binom[c2][a2] * binom[c2 - a2][b2];
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  k %= mint::mod() - 1;
  std::vector<mint> f(tot);
  f[0] = 1;
  if (k <= 100000000 / (tot * tot)) {
    for (int i = 0; i < k; ++i) {
      f = mul(matrix(1, f), coef)[0];
    }
  } else {
    f = mul(matrix(1, f), qpow(coef, k))[0];
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; i + j <= n; ++j) {
      std::cout << f[id[i][j]] << " \n"[i + j == n];
    }
  }
}
