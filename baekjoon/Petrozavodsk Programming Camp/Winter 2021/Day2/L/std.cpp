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

using matrix = std::array<std::array<mint, 6>, 6>;

matrix operator*(const matrix &A, const matrix &B) {
  matrix res;
  for (int i = 0; i < 6; ++i) {
    for (int k = 0; k < 6; ++k) {
      for (int j = 0; j < 6; ++j) {
        res[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return res;
}

matrix qpow(matrix a, long long b) {
  matrix s;
  for (int i = 0; i < 6; ++i) {
    s[i][i] = 1;
  }
  for (; b; b >>= 1) {
    if (b & 1) {
      s = s * a;
    }
    a = a * a;
  }
  return s;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  matrix st = {1, 1, 3, 0, 0, 0};
  matrix A = {0, 0, 5, 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0,
              0, 0, 4, 0, 0, 1, 0, 0, 2, 1, 0, 0, 0, 0, 2, 0, 1, 0};
  while (T--) {
    long long n;
    std::cin >> n;
    std::cout << (st * qpow(A, n))[0][0] << "\n";
  }
}
