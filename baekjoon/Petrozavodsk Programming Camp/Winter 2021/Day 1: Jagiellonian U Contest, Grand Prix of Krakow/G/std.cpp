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

using mint = modint<1000000007>;

class graph {
  int n;
  std::vector<std::vector<int>> E;

  int idx;
  std::vector<int> dfn, low;
  std::vector<int> sta;
  std::vector<int> bcc;

  void tarjan(int u, int fa) {
    dfn[u] = low[u] = idx++;
    sta.push_back(u);
    for (int v : E[u]) {
      if (v != fa) {
        if (dfn[v] == -1) {
          tarjan(v, u);
          low[u] = std::min(low[u], low[v]);
        } else {
          low[u] = std::min(low[u], dfn[v]);
        }
      }
    }
    if (dfn[u] == low[u]) {
      int id = bcc.size();
      bcc.emplace_back();
      int x;
      do {
        x = sta.back();
        sta.pop_back();
        ++bcc[id];
      } while (x != u);
    }
  }

public:
  graph(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  std::vector<int> solve() {
    dfn.assign(n, -1);
    low.resize(n);
    sta.clear();
    idx = 0;
    tarjan(0, -1);
    return bcc;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m, k;
    std::cin >> n >> m >> k;
    graph G(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      G.add_edge(u, v);
    }
    auto s = G.solve();
    
    std::vector<std::array<mint, 2>> f(n + 1);
    f[1][1] = 1;
    for (int i = 1; i < n; ++i) {
      f[i + 1][0] = f[i][0] * (k - 2) + f[i][1] * (k - 1);
      f[i + 1][1] = f[i][0];
    }
    mint ans = k * mint(k - 1).pow(s.size() - 1);
    for (int x : s) {
      if (x > 1) {
        ans *= f[x][0];
      }
    }
    std::cout << ans << "\n";
  }
}
