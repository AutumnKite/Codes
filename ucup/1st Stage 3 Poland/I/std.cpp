#include <bits/stdc++.h>

template<typename Val, 
         typename VV = std::plus<Val>>
class fenwick_tree {
public:
  typedef std::size_t size_type;

protected:
  const Val E;

  size_type n;
  std::vector<Val> val;

  VV fun;

public:
  fenwick_tree() : fenwick_tree(0) {}

  fenwick_tree(size_type _n)
  : E(), n(_n), val(n + 1, E) {}

  fenwick_tree(size_type _n, const Val &_E)
  : E(_E), n(_n), val(n + 1, E) {}

  size_type size() const {
    return n;
  }

  void modify(size_type x, const Val &v) {
    for (++x; x <= n; x += x & -x) {
      val[x] = fun(val[x], v);
    }
  }

  Val query(size_type x) {
    Val s = E;
    for (; x; x ^= x & -x) {
      s = fun(s, val[x]);
    }
    return s;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int T;
  std::cin >> T;
  while (T--) {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    auto val = a;
    std::sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());
    for (int i = 0; i < n; ++i) {
      a[i] = std::lower_bound(val.begin(), val.end(), a[i]) - val.begin();
    }
    std::vector<std::vector<int>> w(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
      fenwick_tree<int> T(val.size());
      for (int j = i; j < n; ++j) {
        w[i][j + 1] = w[i][j] + j - i - T.query(a[j] + 1);
        T.modify(a[j], 1);
      }
    }
    std::vector<int> f(w[0]), g(n + 1);

    auto solve = [&](auto &self, int l, int r, int L, int R) -> void {
      if (l > r) {
        return;
      }
      int i = (l + r) >> 1, p = L;
      g[i] = f[L] + w[L][i];
      for (int j = L + 1; j <= R && j <= i; ++j) {
        int tmp = f[j] + w[j][i];
        if (tmp < g[i]) {
          g[i] = tmp;
          p = j;
        }
      }
      self(self, l, i - 1, L, p);
      self(self, i + 1, r, p, R);
    };

    for (int i = 0; i < k; ++i) {
      solve(solve, 0, n, 0, n);
      f.swap(g);
    }
    std::cout << f[n] << "\n";
  }
}
