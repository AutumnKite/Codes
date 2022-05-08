#include <bits/stdc++.h>

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

  int n, k;
  mint p;
  std::cin >> n >> k >> p;
  std::vector<int> a(n);
  std::vector<mint> inv(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    inv[i] = mint(a[i] + 1).inv();
  }
  std::vector<mint> sum(n + 1);
  for (int i = 0; i < n; ++i) {
    sum[i + 1] = sum[i] + a[i] * inv[i];
  }
  std::vector<mint> prod(n + 1), iprod(n + 1);
  prod[0] = iprod[0] = 1;
  for (int i = 0; i < n; ++i) {
    prod[i + 1] = prod[i] * mint(a[i] + 1);
    iprod[i + 1] = iprod[i] * inv[i];
  }

  mint s1 = 0, s2 = 0, s3 = 0, s4 = 0;
  for (int i = 0; i <= n; ++i) {
    s3 += prod[i];
    s4 += prod[i] * sum[i];
  }
  mint ans = 0;
  for (int i = 0; i < n; ++i) {
    mint v = 0;
    for (int j = 1; j <= a[i]; ++j) {
      v += p.pow(j) * mint(j).pow(k);
    }
    v *= inv[i];
    s1 += iprod[i];
    s2 += iprod[i] * sum[i];
    s3 -= prod[i];
    s4 -= prod[i] * sum[i];
    ans += v * inv[i] * s1 * s3;
    ans += v * s1 * s4;
    ans -= v * s2 * s3;
  }
  std::cout << ans << "\n";
}
