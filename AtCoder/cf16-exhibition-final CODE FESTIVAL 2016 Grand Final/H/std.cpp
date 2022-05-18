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

using bits = std::bitset<300>;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  int r = 0;
  std::vector<bits> S(n);
  for (int i = 0; i < n; ++i) {
    bits a;
    for (int j = 0; j < n; ++j) {
      int x;
      std::cin >> x;
      a[j] = x;
    }
    for (int j = 0; j < n; ++j) {
      if (a[j]) {
        if (S[j].none()) {
          S[j] = a;
          ++r;
          break;
        } else {
          a ^= S[j];
        }
      }
    }
  }

  std::vector<mint> pw(n + 1);
  pw[0] = 1;
  for (int i = 0; i < n; ++i) {
    pw[i + 1] = pw[i] * 2;
  }
  std::vector<mint> pwn(n + 1);
  pwn[0] = 1;
  for (int i = 0; i < n; ++i) {
    pwn[i + 1] = pwn[i] * pw[n];
  }

  std::vector<mint> fac(n + 1), ifac(n + 1);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * (pw[i] - 1);
  }
  ifac[n] = fac[n].inv();
  for (int i = n; i >= 1; --i) {
    ifac[i - 1] = ifac[i] * (pw[i] - 1);
  }
  std::vector<mint> f(n + 1);
  f[0] = 1;
  for (int i = 0; i < n; ++i) {
    f[i + 1] = f[i] * (pw[n] - pw[i]);
  }

  auto calc = [&](int n, int m) {
    return fac[n] * ifac[m] * ifac[n - m] * f[m];
  };

  mint ans = 0;
  for (int i = r; i <= n; ++i) {
    ans += calc(n, i) * pwn[n - i] * calc(i, r);
  }
  std::cout << ans * calc(n, r).inv() << "\n";
}
