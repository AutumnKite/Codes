#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P, "P must be a positive integer");

  using mint = modint<P>;

protected:
  unsigned v;

public:
  modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  modint(T t_v) : v() {
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
  modint(T t_v) : v() {
    v = t_v % P;
  }

  unsigned val() const {
    return v;
  }

  static unsigned mod() {
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

using mint = modint<1000000007>;

using matrix = std::vector<std::vector<mint>>;

matrix transpose(const matrix &a) {
  int n = a.size(), m = a[0].size();
  matrix res(m, std::vector<mint>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      res[j][i] = a[i][j];
    }
  }
  return res;
}

matrix cosubmatrix(const matrix &a, int x, int y) {
  int n = a.size(), m = a[0].size();
  matrix res(n - 1, std::vector<mint>(m - 1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i != x && j != y) {
        res[i - (i > x)][j - (j > y)] = a[i][j];
      }
    }
  }
  return res;
}

int gauss(matrix a, std::vector<mint> &x) {
  int n = a.size();
  x.assign(n, mint());
  std::vector<int> p(n, n);
  int now = 0;
  for (int i = 0; i < n; ++i) {
    int k = -1;
    for (int j = now; j < n; ++j) {
      if (a[j][i].val()) {
        k = j;
        break;
      }
    }
    if (k == -1) {
      x[i] = 1;
      continue;
    }
    if (k != now) {
      a[now].swap(a[k]);
    }
    mint t = a[now][i].inv();
    for (int j = i; j < n; ++j) {
      a[now][j] *= t;
    }
    for (int j = 0; j < n; ++j) {
      if (j != now && a[j][i].val()) {
        mint t = -a[j][i];
        for (int k = i; k < n; ++k) {
          a[j][k] += a[now][k] * t;
        }
      }
    }
    p[now] = i;
    ++now;
  }
  for (int i = 0; i < now; ++i) {
    for (int j = p[i] + 1; j < n; ++j) {
      x[p[i]] -= a[i][j];
    }
  }
  return now;
}

bool inv(matrix a, matrix &b) {
  int n = a.size();
  b.assign(n, std::vector<mint>(n));
  for (int i = 0; i < n; ++i) {
    b[i][i] = 1;
  }
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
      a[i].swap(a[k]);
      b[i].swap(b[k]);
    }
    mint t = a[i][i].inv();
    for (int j = i; j < n; ++j) {
      a[i][j] *= t;
    }
    for (int j = 0; j < n; ++j) {
      b[i][j] *= t;
    }
    for (int j = 0; j < n; ++j) {
      if (j != i && a[j][i].val()) {
        mint t = -a[j][i];
        for (int k = i; k < n; ++k) {
          a[j][k] += a[i][k] * t;
        }
        for (int k = 0; k < n; ++k) {
          b[j][k] += b[i][k] * t;
        }
      }
    }
  }
  return true;
}

mint det(matrix a) {
  int n = a.size();
  mint ans = 1;
  for (int i = 0; i < n; ++i) {
    int k = -1;
    for (int j = i; j < n; ++j) {
      if (a[j][i].val()) {
        k = j;
        break;
      }
    }
    if (k == -1) {
      return mint();
    }
    if (k != i) {
      a[i].swap(a[k]);
      ans = -ans;
    }
    mint inv = a[i][i].inv();
    for (int j = 0; j < n; ++j) {
      if (j != i && a[j][i].val()) {
        mint t = -a[j][i] * inv;
        for (int k = i; k < n; ++k) {
          a[j][k] += a[i][k] * t;
        }
      }
    }
    ans *= a[i][i];
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<mint>> a(n, std::vector<mint>(n));
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      ++a[v][v];
      --a[u][v];
    }
    std::vector<mint> x, y;
    int rank = gauss(a, x);

    if (n == 1) {
      std::cout << 1 << "\n";
      continue;
    }

    if (rank < n - 1) {
      for (int i = 0; i < n; ++i) {
        std::cout << 0 << " \n"[i == n - 1];
      }
      continue;
    }

    if (rank == n) {
      matrix b;
      inv(a, b);
      mint d = det(a);
      for (int i = 0; i < n; ++i) {
        std::cout << b[i][i] * d << " \n"[i == n - 1];
      }
      continue;
    }

    gauss(transpose(a), y);
    int r = 0, c = 0;
    while (!x[r].val()) {
      ++r;
    }
    while (!y[c].val()) {
      ++c;
    }
    mint d = det(cosubmatrix(a, c, r)) * x[r].inv() * y[c].inv();
    if ((r + c) & 1) {
      d = -d;
    }
    for (int i = 0; i < n; ++i) {
      std::cout << x[i] * y[i] * d << " \n"[i == n - 1];
    }
  }
}
