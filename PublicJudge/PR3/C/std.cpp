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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, n;
  std::cin >> m >> n;
  std::vector<mint> a(m + 1);
  for (int i = 0; i <= m; ++i) {
    std::cin >> a[i];
  }
  std::vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> b[i];
  }

  mint prod = 1;
  mint inv = std::accumulate(a.begin(), a.end(), mint()).inv();
  for (int i = 0; i < n; ++i) {
    prod *= b[i];
    inv = inv.pow(b[i]);
  }

  std::vector<std::vector<mint>> f(n + 1, std::vector<mint>(m + 1));
  f[0] = a;
  for (int i = 1; i <= m; ++i) {
    f[0][i] += f[0][i - 1];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j <= m; ++j) {
      f[i + 1][j] += f[i][j].pow(b[i]);
      f[i + 1][j] -= f[i][i].pow(b[i]);
    }
    for (int j = i; j <= m; ++j) {
      f[i][j] = f[i][j].pow(b[i] - 1);
    }
  }

  std::vector<mint> c(m + 1);
  c[m] = 1;
  for (int i = n - 1; i >= 0; --i) {
    std::vector<mint> nc(m + 1);
    for (int j = i + 1; j <= m; ++j) {
      nc[j] += f[i][j] * c[j];
      nc[i] -= f[i][i] * c[j];
    }
    c.swap(nc);
  }

  for (int k = 0; k <= m; ++k) {
    mint ans = 0;
    for (int i = k; i <= m; ++i) {
      ans += a[k] * c[i];
    }
    std::cout << ans * prod * inv << "\n";
  }
}
