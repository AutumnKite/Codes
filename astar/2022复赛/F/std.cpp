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

class suffix_array {
  int n, m;
  std::vector<int> rk, id, sa, h;

  void radix_sort() {
    std::vector<int> cnt(m);
    for (int i = 0; i < n; ++i) {
      ++cnt[rk[i]];
    }
    for (int i = 1; i < m; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      sa[--cnt[rk[id[i]]]] = id[i];
    }
  }

  bool cmp(int x, int y, int l) {
    if (id[x] != id[y]) return false;
    x += l, y += l;
    return x < n && y < n && id[x] == id[y];
  }

public:
  suffix_array(std::string s) : n(s.size()), m(), rk(n), id(n), sa(n), h(n) {
    for (int i = 0; i < n; ++i) {
      rk[i] = s[i];
      m = std::max(m, rk[i] + 1);
      id[i] = i;
    }
    radix_sort();
    for (int l = 1, p = 0; p < n; m = p, l <<= 1) {
      p = 0;
      for (int i = n - l; i < n; ++i) {
        id[p++] = i;
      }
      for (int i = 0; i < n; ++i) {
        if (sa[i] >= l) {
          id[p++] = sa[i] - l;
        }
      }
      radix_sort();
      std::swap(rk, id);
      p = 1, rk[sa[0]] = 0;
      for (int i = 1; i < n; ++i) {
        if (!cmp(sa[i - 1], sa[i], l)) {
          ++p;
        }
        rk[sa[i]] = p - 1;
      }
    }
    h[0] = 0;
    for (int i = 0, k = 0; i < n; ++i) {
      if (!rk[i]) {
        continue;
      }
      k = std::max(k - 1, 0);
      int j = sa[rk[i] - 1];
      while (i + k < n && s[i + k] == s[j + k]) {
        ++k;
      }
      h[rk[i]] = k;
    }
  }

  int rank(int i) const  {
    return rk[i];
  }

  int kth(int i) const {
    return sa[i];
  }

  int height(int i) const {
    return h[i];
  }
};

struct query {
  int l, r, bl, id;

  bool operator<(const query &rhs) const {
    if (bl != rhs.bl) {
      return bl < rhs.bl;
    }
    return bl & 1 ? (r > rhs.r) : (r < rhs.r);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;
  suffix_array A(s);
  int n = s.size(), k, q;
  std::cin >> k >> q;
  const int B = n / sqrt(q);
  std::vector<query> Q(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> Q[i].l >> Q[i].r;
    --Q[i].l, --Q[i].r;
    Q[i].bl = Q[i].l / B;
    Q[i].id = i;
  }

  if (k == 0) {
    for (int i = 0; i < q; ++i) {
      std::cout << 1 << "\n";
    }
    return 0;
  }

  std::sort(Q.begin(), Q.end());

  std::vector<int> col(n);
  int idx = 0;
  for (int i = 1; i < n; ++i) {
    if (A.height(i) < k) {
      col[A.kth(i)] = ++idx;
    } else {
      col[A.kth(i)] = idx;
    }
  }
  ++idx;
  std::vector<mint> ways(n + 1);
  for (int i = 1; i <= n; ++i) {
    ways[i] = mint(2).pow(i) - i - 1;
  }
  std::vector<int> cnt(idx);
  mint now = 0;

  auto add = [&](int x, int v) {
    now -= ways[cnt[x]];
    cnt[x] += v;
    now += ways[cnt[x]];
  };

  int l = 0, r = -1;
  std::vector<mint> ans(q);
  for (int i = 0; i < q; ++i) {
    while (r < Q[i].r) {
      add(col[++r], 1);
    }
    while (l > Q[i].l) {
      add(col[--l], 1);
    }
    while (r > Q[i].r) {
      add(col[r--], -1);
    }
    while (l < Q[i].l) {
      add(col[l++], -1);
    }
    ans[Q[i].id] = now * mint(2).pow(Q[i].r - Q[i].l + 1).inv();
  }
  for (auto x : ans) {
    std::cout << x << "\n";
  }
}
