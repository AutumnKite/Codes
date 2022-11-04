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

  int n;
  std::cin >> n;
  std::vector<int> R(60);
  for (int i = 0; i < n; ++i) {
    long long x;
    std::cin >> x;
    for (int j = 0; j < 60; ++j) {
      R[j] |= (x >> j & 1) << i;
    }
  }
  std::string b;
  std::cin >> b;

  std::vector<mint> f(1 << n);
  f[(1 << n) - 1] = 1;
  for (int k = 59; k >= 0; --k) {
    R[k] = ((1 << n) - 1) ^ R[k];
    std::vector<int> p, q;
    for (int i = 0; i < n; ++i) {
      if (R[k] >> i & 1) {
        p.push_back(i);
      } else {
        q.push_back(i);
      }
    }
    std::vector<mint> sum(1 << n);
    for (int S = 0; S < (1 << n); ++S) {
      sum[S] = b[S] - '0';
    }
    for (int i : p) {
      for (int S = 0; S < (1 << n); ++S) {
        if (S >> i & 1) {
          sum[S] += sum[S ^ (1 << i)];
        }
      }
    }
    for (int i : q) {
      for (int S = 0; S < (1 << n); ++S) {
        if (S >> i & 1) {
          f[S ^ (1 << i)] += f[S];
        }
      }
    }
    std::vector<mint> g(1 << n);
    for (int S = R[k]; ; S = (S - 1) & R[k]) {
      for (int T = R[k]; T < (1 << n); T = (T + 1) | R[k]) {
        g[T] = sum[T ^ S];
      }
      for (int i : q) {
        for (int T = R[k]; T < (1 << n); T = (T + 1) | R[k]) {
          if (T >> i & 1) {
            g[T ^ (1 << i)] += g[T];
          }
        }
      }
      for (int T = R[k]; T < (1 << n); T = (T + 1) | R[k]) {
        f[T ^ R[k] ^ S] *= g[T];
      }
      if (!S) {
        break;
      }
    }
    for (int i : q) {
      for (int S = 0; S < (1 << n); ++S) {
        if (S >> i & 1) {
          f[S ^ (1 << i)] -= f[S];
        }
      }
    }
  }
  std::cout << std::accumulate(f.begin(), f.end(), mint()) << "\n";
}
