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

using mint = modint<998244353>;

const int id[6] = {0, 3, 5, 1, 2, 4};

const int trans[6][6] = {
  0, 1, 2, 3, 4, 5,
  1, 2, 0, 5, 3, 4,
  2, 0, 1, 4, 5, 3,
  3, 4, 5, 0, 1, 2,
  4, 5, 3, 2, 0, 1,
  5, 3, 4, 1, 2, 0
};

bool solve(std::vector<std::vector<mint>> a, 
           std::vector<mint> b,
           std::vector<mint> &res) {
  int n = a.size();
  for (int i = 0; i < n; ++i) {
    int k = -1;
    for (int j = i; j < n; ++j) {
      if (a[j][i].val()) {
        k = j;
        break;
      }
    }
    if (k == -1) {
      return false;
    }
    if (k != i) {
      std::swap(a[i], a[k]);
      std::swap(b[i], b[k]);
    }
    mint inv = a[i][i].inv();
    for (int j = 0; j < n; ++j) {
      if (j != i && a[j][i].val()) {
        mint t = -a[j][i] * inv;
        for (int k = i; k < n; ++k) {
          a[j][k] += a[i][k] * t;
        }
        b[j] += b[i] * t;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    b[i] *= a[i][i].inv();
  }
  res = std::move(b);
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> pw(n + 1);
  pw[0] = 1;
  for (int i = 0; i < n; ++i) {
    pw[i + 1] = pw[i] * 6;
  }

  std::vector<mint> p(pw[n]);
  mint m = 1;
  for (int i = 0; i < pw[n]; ++i) {
    mint v;
    std::cin >> v;
    int S = 0;
    for (int j = 0; j < n; ++j) {
      S += id[i / pw[j] % 6] * pw[j];
    }
    p[S] = v;
    m += v;
  }
  mint invm = m.inv();

  std::vector<std::vector<mint>> a(pw[n], std::vector<mint>(pw[n]));
  std::vector<mint> b(pw[n]);
  for (int i = 0; i < pw[n]; ++i) {
    for (int j = 0; j < pw[n]; ++j) {
      int t = 0;
      for (int k = 0; k < n; ++k) {
        t += trans[i / pw[k] % 6][j / pw[k] % 6] * pw[k];
      }
      a[t][i] = p[j] * invm;
    }
  }
  for (int i = 0; i < pw[n]; ++i) {
    --a[i][i];
  }
  --b[0];
  std::vector<mint> res;
  if (solve(a, b, res)) {
    unsigned ans = 0;
    for (auto x : res) {
      ans ^= (x * invm).val();
    }
    std::cout << ans << "\n";
  } else {
    std::cout << -1 << "\n";
  }
}
