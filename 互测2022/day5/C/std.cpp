#include <bits/stdc++.h>

template<unsigned id>
class dynamic_modint {
  using mint = dynamic_modint<id>;

protected:
  static unsigned P;

  unsigned v;

public:
  dynamic_modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  dynamic_modint(T t_v) : v() {
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
  dynamic_modint(T t_v) : v() {
    v = t_v % P;
  }

  unsigned val() const {
    return v;
  }

  static unsigned mod() {
    return P;
  }

  static void set_mod(unsigned nP) {
    P = nP;
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
    v ? --v : v = P - 1;
    return *this;
  }
  
  mint operator--(int) {
    mint tmp = *this;
    v ? --v : v = P - 1;
    return tmp;
  }

  mint operator-() const {
    mint res;
    res.v = v ? P - v : 0;
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

template<unsigned id>
unsigned dynamic_modint<id>::P;

using mint = dynamic_modint<0>;
using mint1 = dynamic_modint<1>;
using mint2 = dynamic_modint<2>;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, mod;
  std::cin >> n >> m >> mod;
  mint::set_mod(m);
  mint1::set_mod(mod - 1);
  mint2::set_mod(mod);

  std::vector<int> cnt(n + 1);
  cnt[0] = 1;
  if (n == 1) {
    cnt[1] = m - 2;
  }
  if (n == 2) {
    if (m == 2) {
      cnt[1] = 3, cnt[2] = 2;
    } else {
      cnt[1] = 20, cnt[2] = 27;
    }
  }
  if (n == 3) {
    if (m == 2) {
      cnt[1] = 21, cnt[2] = 98, cnt[3] = 48;
    } else {
      cnt[1] = 221, cnt[2] = 4719, cnt[3] = 6291;
    }
  }
  mint2 ans = 0;
  for (int i = 0; i <= n; ++i) {
    ans += cnt[i] * mint2(3).pow(mint1(m).pow(n * (n - i)).val());
  }
  std::cout << ans << "\n";
}
