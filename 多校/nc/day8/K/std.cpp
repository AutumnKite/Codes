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

void FMT(int n, std::vector<mint> &f) {
  for (int i = 0; i < n; ++i) {
    for (int S = 0; S < (1 << n); ++S) {
      if (S >> i & 1) {
        f[S] += f[S ^ (1 << i)];
      }
    }
  }
}

void IFMT(int n, std::vector<mint> &f) {
  for (int i = 0; i < n; ++i) {
    for (int S = 0; S < (1 << n); ++S) {
      if (S >> i & 1) {
        f[S] -= f[S ^ (1 << i)];
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<mint> a(1 << m);
  for (int i = 0; i < n; ++i) {
    int k;
    std::cin >> k;
    int mask = 0;
    for (int j = 0; j < k; ++j) {
      int x;
      std::cin >> x;
      --x;
      mask |= 1 << x;
    }
    ++a[mask];
  }
  FMT(m, a);
  std::vector<mint> now(1 << m, 1);
  std::vector<bool> ok(1 << m);
  ok[0] = true;
  for (int k = 1; k <= m; ++k) {
    for (int i = 0; i < (1 << m); ++i) {
      now[i] *= a[i];
    }
    auto tmp = now;
    IFMT(m, tmp);
    for (int i = 0; i < m; ++i) {
      for (int S = 0; S < (1 << m); ++S) {
        if (S >> i & 1) {
          tmp[S ^ (1 << i)] += tmp[S];
        }
      }
    }
    int cnt = 0;
    for (int i = 0; i < (1 << m); ++i) {
      if (!ok[i] && tmp[i].val()) {
        ok[i] = true;
        ++cnt;
      }
    }
    std::cout << cnt << " \n"[k == m];
  }
}
