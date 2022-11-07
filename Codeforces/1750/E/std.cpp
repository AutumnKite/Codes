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
    int n;
    std::cin >> n;
    std::string a;
    std::cin >> a;
    std::vector<int> s(n + 1);
    for (int i = 0; i < n; ++i) {
      s[i + 1] = s[i] + (a[i] == '(' ? 1 : -1);
    }
    int min = *std::min_element(s.begin(), s.end());
    for (int i = 0; i <= n; ++i) {
      s[i] -= min;
    }

    fenwick_tree<long long> T(n + 1), Ti(n + 1);
    long long ans = 0;

    auto solve = [&](auto &self, int l, int r) -> void {
      if (l + 1 == r) {
        return;
      }
      int mid = (l + r) >> 1;
      {
        int p = mid - 1, min = n;
        for (int i = mid; i < r; ++i) {
          min = std::min(min, s[i]);
          while (p >= l && s[p] > min) {
            T.modify(s[p], 1);
            Ti.modify(s[p], s[p]);
            --p;
          }
          ans += T.query(s[i]) * (s[i] - min);
          ans += Ti.query(n + 1) - Ti.query(s[i]) -
                 (T.query(n + 1) - T.query(s[i])) * min;
        }
        while (p + 1 < mid) {
          ++p;
          T.modify(s[p], -1);
          Ti.modify(s[p], -s[p]);
        }
      }
      {
        int p = mid, min = n;
        for (int i = mid - 1; i >= l; --i) {
          min = std::min(min, s[i]);
          while (p < r && s[p] >= min) {
            T.modify(s[p], 1);
            Ti.modify(s[p], s[p]);
            ++p;
          }
          ans += T.query(s[i]) * (s[i] - min);
          ans += Ti.query(n + 1) - Ti.query(s[i]) -
                 (T.query(n + 1) - T.query(s[i])) * min;
        }
        while (p - 1 >= mid) {
          --p;
          T.modify(s[p], -1);
          Ti.modify(s[p], -s[p]);
        }
      }
      self(self, l, mid);
      self(self, mid, r);
    };

    solve(solve, 0, n + 1);
    std::cout << ans << "\n";
  }
}
