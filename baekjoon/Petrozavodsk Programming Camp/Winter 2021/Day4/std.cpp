#include <bits/stdc++.h>

class disjoint_set {
public:
  typedef std::size_t size_type;

protected:
  std::vector<size_type> fa;

public:
  disjoint_set(size_type n = 0) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  size_type find(size_type x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
  }

  bool merge(size_type x, size_type y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    fa[y] = x;
    return true;
  }
};

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

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int period(const std::string &s) {
  int n = s.size();
  std::vector<int> fail(n + 1, -1);
  fail[1] = 0;
  for (int i = 1, j = 0; i < n; ++i) {
    while (j && s[j] != s[i]) {
      j = fail[j];
    }
    if (s[j] == s[i]) {
      ++j;
    }
    fail[i + 1] = j;
  }
  int d = n - fail[n];
  if (n % d == 0) {
    return d;
  } else {
    return n;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::vector<bool>> E(n, std::vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int x;
      std::cin >> x;
      E[i][j] = E[j][i] = !x;
    }
  }
  int m;
  std::cin >> m;
  std::vector<int> a(m);
  std::vector<std::vector<int>> pos(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> a[i];
    pos[--a[i]].push_back(i);
  }

  disjoint_set D(n);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (E[i][j] && !pos[i].empty() && !pos[j].empty()) {
        D.merge(i, j);
      }
    }
  }
  std::vector<int> g(n);
  for (int i = 0; i < n; ++i) {
    g[D.find(i)] = gcd(g[D.find(i)], pos[i].size());
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (E[i][j] && !pos[i].empty() && !pos[j].empty()) {
        std::string s;
        auto pi = pos[i].begin(), pj = pos[j].begin();
        while (pi != pos[i].end() || pj != pos[j].end()) {
          if (pj == pos[j].end() || (pi != pos[i].end() && *pi < *pj)) {
            s.push_back('0');
            ++pi;
          } else {
            s.push_back('1');
            ++pj;
          }
        }
        g[D.find(i)] = gcd(g[D.find(i)], s.size() / period(s));
      }
    }
  }

  std::vector<std::vector<int>> ans;
  for (int rt = 0; rt < n; ++rt) {
    if ((int)D.find(rt) == rt) {
      if (pos[rt].empty()) {
        bool ok = true;
        for (int i = 0; i < n; ++i) {
          if (!pos[i].empty()) {
            ok &= !E[rt][i];
          }
        }
        if (ok) {
          ans.emplace_back(1, rt);
        }
        continue;
      }
      std::vector<int> id(n, -1);
      std::vector<int> u;
      for (int i = 0; i < n; ++i) {
        if ((int)D.find(i) == rt) {
          id[i] = u.size();
          u.push_back(i);
        }
      }
      int z = u.size();
      std::vector<int> cnt(z);
      std::vector<int> s;
      for (int i = 0; i < m; ++i) {
        if (id[a[i]] != -1) {
          int t = id[a[i]];
          if (cnt[t] < (int)pos[a[i]].size() / g[rt]) {
            s.push_back(t);
            ++cnt[t];
          }
        }
      }
      std::vector<std::vector<bool>> G(z, std::vector<bool>(z));
      for (int x : u) {
        for (int y = 0; y < n; ++y) {
          if (E[x][y] && id[y] != -1) {
            G[id[x]][id[y]] = true;
          }
        }
      }

      std::vector<int> head(z), deg(z);

      auto add = [&](int i) {
        while (head[i] < (int)s.size() && s[head[i]] != i) {
          deg[i] += G[s[head[i]]][i];
          ++head[i];
        }
      };

      for (int i = 0; i < z; ++i) {
        add(i);
      }
      std::vector<int> ns;
      while (ns.size() < s.size()) {
        for (int i = 0; i < z; ++i) {
          if (head[i] < (int)s.size() && !deg[i]) {
            ns.push_back(u[i]);
            for (int j = 0; j < z; ++j) {
              deg[j] -= G[i][j];
            }
            ++head[i];
            add(i);
            break;
          }
        }
      }
      ans.push_back(ns);
    }
  }
  std::sort(ans.begin(), ans.end());
  for (const auto &p : ans) {
    mint sum = 0, pw = 1;
    for (int x : p) {
      sum += (x + 1) * pw;
      pw *= n + 1;
    }
    std::cout << sum << "\n";
  }
}
