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

constexpr mint inv2 = mint(2).inv(), inv6 = mint(6).inv();

mint calc(long long n) {
  return inv6 * n * (n + 1) * (2 * n + 1);
}

mint calc(long long l, long long r) {
  if (l == 0) {
    return calc(r);
  }
  return calc(r) - calc(l - 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    long long sx, sy, tx, ty;
    std::cin >> sx >> sy >> tx >> ty;
    mint ans = mint(tx).pow(2) * mint(ty).pow(2) -
               mint(sx).pow(2) * mint(sy).pow(2) -
               mint(tx).pow(2) - mint(ty).pow(2);
    ans *= 2;
    long long sa = sx + sy, sb = sx - sy;
    long long ta = tx + ty, tb = tx - ty;
    if (sb <= 0 && tb <= 0) {
      sb = -sb;
      tb = -tb;
    }
    if (sa > ta) {
      std::swap(sa, ta);
    }
    if (sb > tb) {
      std::swap(sb, tb);
    }
    if (ta - sa > tb - sb) {
      ans += calc(sa, ta);
      if (sb >= 0 && tb >= 0 && sb + tb >= ta - sa) {
        long long a = ((ta - sa) + (tb - sb)) / 2;
        long long b = ((ta - sa) - (tb - sb)) / 2;
        ans += calc(sb - b + 1, sb);
        ans += calc(sb - b, tb);
      } else {
        ans += calc(1, std::abs(sb));
        ans += calc(0, tb);
        ans += (ta - sa - std::abs(sb) - tb) / 2;
      }
      std::cout << ans * inv2 << "\n";
    } else {
      long long a = ((tb - sb) + (ta - sa)) / 2;
      long long b = ((tb - sb) - (ta - sa)) / 2;
      ans += calc(sb, tb);
      ans += calc(sa - b + 1, sa);
      ans += calc(sa - b, ta);
      std::cout << ans * inv2 << "\n";
    }
  }
}
