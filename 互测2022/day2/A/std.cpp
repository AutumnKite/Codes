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

  int n, m, c;
  std::cin >> n >> m >> c;
  std::vector<std::pair<int, int>> seg;
  for (int i = 0; i < m; ++i) {
    int l, r;
    std::cin >> l >> r;
    --l;
    seg.emplace_back(l, r);
  }
  std::vector f(n + 1, std::vector(n + 1, std::vector<mint>(n + 1))), g(f);
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      f[i][i][j] = g[i][i][j] = 1;
    }
  }
  for (int l = n - 1; l >= 0; --l) {
    for (int r = l + 1; r <= n; ++r) {
      for (int i = 1; i <= n; ++i) {
        for (int k = l; k < r; ++k) {
          g[l][r][i] += f[l][k][i - 1] * g[k + 1][r][i];
        }
      }
      std::vector<int> d(r - l + 1);
      for (auto [pl, pr] : seg) {
        if (l <= pl && pr <= r) {
          ++d[pl - l], --d[pr - l];
        }
      }
      std::partial_sum(d.begin(), d.end(), d.begin());
      d.pop_back();
      if (std::find(d.begin(), d.end(), 0) != d.end()) {
        continue;
      }
      for (int i = 1; i <= n; ++i) {
        f[l][r][i] = f[l][r][i - 1];
        for (int k = l; k < r; ++k) {
          f[l][r][i] += f[l][k][i - 1] * g[k + 1][r][i];
        }
        g[l][r][i] += f[l][r][i - 1];
      }
    }
  }

  std::vector C(n + 1, std::vector<mint>(n + 1));
  for (int i = 0; i <= n; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
  auto h = g[0][n];
  mint now = 1, ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      h[i] -= C[i][j] * h[j];
    }
    now *= c - i + 1;
    now *= mint(i).inv();
    ans += h[i] * now;
  }
  std::cout << ans << "\n";
}
