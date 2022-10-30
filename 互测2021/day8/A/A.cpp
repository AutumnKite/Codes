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
           typename std::enable_if<
                    std::is_signed<T>::value
                    && std::is_integral<T>::value,
                    bool>::type = true>
  dynamic_modint(T _v) {
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
  dynamic_modint(T _v) {
    v = _v % P;
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

template<unsigned id>
unsigned dynamic_modint<id>::P;

using mint = dynamic_modint<0>;

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

  int n, mod, sub_id;
  std::cin >> n >> mod >> sub_id;
  mint::set_mod(mod);
  std::vector<int> l(n);
  std::vector<mint> p(n), d(n);
  mint tot = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> l[i] >> p[i] >> d[i];
    tot += p[i];
  }
  tot = tot.inv();
  for (int i = 0; i < n; ++i) {
    p[i] *= tot;
  }

  if (n == 1) {
    std::cout << l[0] << "\n";
    return 0;
  }

  std::vector<int> prod(n + 1);
  prod[0] = 1;
  for (int i = 0; i < n; ++i) {
    prod[i + 1] = prod[i] * l[i];
  }

  mint ans = 1;
  for (int ban = 1; ban < prod[n]; ++ban) {
    std::vector<std::vector<mint>> A(prod[n], std::vector<mint>(prod[n]));
    std::vector<mint> b(prod[n]);
    for (int S = 0; S < prod[n]; ++S) {
      A[S][S] = 1;
    }
    b[0] = 1;
    std::vector<std::pair<int, int>> to;
    for (int S = 0; S < prod[n]; ++S) {
      for (int i = 0; i < n; ++i) {
        int v = S / prod[i] % l[i];
        int nv = (v + 1) % l[i];
        int T = S - v * prod[i] + nv * prod[i];
        if (T == ban) {
          continue;
        }
        if (T == 0) {
          to.emplace_back(S, i);
          continue;
        }
        A[T][S] -= p[i];
      }
    }
    std::vector<mint> res;
    solve(A, b, res);
    mint s = 0;
    for (auto [S, i] : to) {
      s += res[S] * p[i];
    }
    ans += 1 - s;
  }
  std::cout << ans << "\n";
}
