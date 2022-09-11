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

int n, m, L;
mint f[50000][26][21], sum[50000], pre0[26][21], pre1[26][21];
std::vector<int> E[50000];
int size[50000];

void dfs(int u, int fa) {
  size[u] = 1;
  f[u][1][0] = 1;
  for (int v : E[u]) {
    if (v != fa) {
      dfs(v, u);
      for (int i = 1; i <= size[u] && i <= m; ++i) {
        pre0[i][0] = f[u][i][0];
        for (int j = 1; j <= L; ++j) {
          pre0[i][j] = f[u][i][j] + pre0[i][j - 1];
        }
        for (int j = 0; j <= L; ++j) {
          f[u][i][j] *= sum[v];
        }
      }
      for (int i = 1; i <= size[v] && i <= m; ++i) {
        for (int j = 1; j <= L; ++j) {
          pre1[i][j] = f[v][i][j - 1] + pre1[i][j - 1];
        }
      }
      for (int i = 1; i <= size[u] && i <= m; ++i) {
        for (int j = 1; j <= size[v] && i + j <= m; ++j) {
          for (int k = 1; k <= L; ++k) {
            f[u][i + j][k] += (pre0[i][k] - pre0[i][k - 1]) *
                              pre1[j][std::min(k, L - k)];
            f[u][i + j][k] += (pre1[j][k] - pre1[j][k - 1]) *
                              pre0[i][std::min(k - 1, L - k)];
          }
        }
      }
      size[u] += size[v];
    }
  }
  for (int i = 1; i <= size[u] && i <= m; ++i) {
    for (int j = 0; j <= L; ++j) {
      sum[u] += f[u][i][j];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> L;
  L <<= 1;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  dfs(0, -1);
  std::cout << sum[0] << "\n";
}
