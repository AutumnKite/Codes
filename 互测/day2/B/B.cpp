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

mint solve_small_k(int n, int k, std::string pre) {
  int st = 0;
  for (int i = 0; i < (int)pre.size(); ++i) {
    st = st << 1 | (pre[i] - '0');
  }

  std::vector<int> bitcnt(1 << k);
  for (int S = 1; S < (1 << k); ++S) {
    bitcnt[S] = bitcnt[S >> 1] + (S & 1);
  }

  int all = (1 << k) - 1;
  std::vector<mint> f(1 << k);
  f[st] = 1;
  for (int i = (int)pre.size() + 1; i <= n; ++i) {
    std::vector<mint> g(1 << k);
    for (int S = 0; S < (1 << k); ++S) {
      if (f[S].val()) {
        for (int v = 0; v < 2; ++v) {
          int T = ((S << 1) & all) | v;
          if (i < k || bitcnt[T] != (k >> 1)) {
            g[T] += f[S];
          }
        }
      }
    }
    f.swap(g);
  }
  return std::accumulate(f.begin(), f.end(), mint(0));
}

mint det(std::vector<std::vector<mint>> a) {
  int n = a.size();
  std::vector<mint> f(1 << n);
  f[0] = 1;
  for (int S = 0; S < (1 << n); ++S) {
    int t = __builtin_popcount(S);
    int now = t;
    for (int i = 0; i < n; ++i) {
      if (!(S >> i & 1)) {
        if (now & 1) {
          f[S | (1 << i)] -= f[S] * a[t][i];
        } else {
          f[S | (1 << i)] += f[S] * a[t][i];
        }
      } else {
        --now;
      }
    }
  }
  return f.back();
}

mint part(int n, int k, std::string pre) {
  int m = pre.size(), t = n / k;
  int delta = k / 2 * t;
  int W = k, H = k / 2 - 1 + delta;
  std::vector vis(W + 1, std::vector(H + 1, false));
  int s = 0;
  for (int i = 0; i < m; ++i) {
    vis[i][s + delta] = true;
    s += pre[i] == '1';
    if (s >= k / 2) {
      return mint();
    }
  }
  for (int i = 0; i <= m; ++i) {
    for (int j = s + delta; j <= H; ++j) {
      if (i == m && j == s + delta) {
        continue;
      }
      vis[i][j] = true;
    }
  }
  mint ans = 0;
  for (int r = s; r <= (t + 1) * (k / 2 - 1); ++r) {
    auto nvis(vis);
    for (int i = n % k; i <= k; ++i) {
      for (int j = 0; j <= r; ++j) {
        if (i == n % k && j == r) {
          continue;
        }
        nvis[i][j] = true;
      }
    }
    std::vector f(H + 1, std::vector(W + 1, std::vector(H + 1, mint())));
    for (int p = 0; p <= H; ++p) {
      if (!nvis[0][p]) {
        f[p][0][p] = 1;
        for (int i = 1; i <= W; ++i) {
          for (int j = 0; j <= H; ++j) {
            if (!nvis[i][j]) {
              f[p][i][j] = f[p][i - 1][j];
              if (j) {
                f[p][i][j] += f[p][i - 1][j - 1];
              }
            }
          }
        }
      }
    }
    std::vector g(W + 1, std::vector(H + 1, mint()));
    if (!nvis[m][s + delta]) {
      g[m][s + delta] = 1;
      for (int i = m + 1; i <= W; ++i) {
        for (int j = 0; j <= H; ++j) {
          if (!nvis[i][j]) {
            g[i][j] = g[i - 1][j];
            if (j) {
              g[i][j] += g[i - 1][j - 1];
            }
          }
        }
      }
    }

    std::vector<int> sum(t + 2);

    auto dfs = [&](auto &self, int p) -> void {
      if (p > t) {
        std::vector A(t + 1, std::vector(t + 1, mint()));
        for (int i = 1; i <= t; ++i) {
          for (int j = 0; j < t; ++j) {
            A[i][j] = f[sum[i] + delta - k / 2 * i]
                       [k][sum[j + 1] + delta - k / 2 * j];
          }
          A[i][t] = f[sum[i] + delta - k / 2 * i]
                     [n % k][sum[t + 1]];
        }
        for (int j = 0; j < t; ++j) {
          A[0][j] = g[k][sum[j + 1] + delta - k / 2 * j];
        }
        A[0][t] = g[n % k][sum[t + 1]];
        ans += det(A);
        return;
      }
      for (int i = 0; i < k / 2; ++i) {
        if (sum[p] + i <= std::min(r, (p + 1) * (k / 2 - 1))
            && sum[p] + i + (t - p) * (k / 2 - 1) >= r) {
          sum[p + 1] = sum[p] + i;
          self(self, p + 1);
        }
      }
    };

    sum[0] = s;
    dfs(dfs, 0);
  }
  return ans;
}

mint solve_large_k(int n, int k, std::string pre) {
  mint ans = part(n, k, pre);
  for (char &c : pre) {
    if (c == '0') {
      c = '1';
    } else {
      c = '0';
    }
  }
  return ans + part(n, k, pre);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k, m;
  std::cin >> n >> k >> m;
  std::string pre;
  if (m > 0) {
    std::cin >> pre;
  }

  if (k <= 22) {
    std::cout << solve_small_k(n, k, pre) << "\n";
  } else {
    std::cout << solve_large_k(n, k, pre) << "\n";
  }
}
