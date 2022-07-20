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

class suffix_array {
	int n;
  std::vector<int> sa, rk, h;

public:
	suffix_array(std::string s) : n(s.size()), sa(n), rk(n), h(n) {
    std::vector<int> id(n);
    int m = 0;

    auto radix_sort = [&]() {
      std::vector<int> cnt(m);
      for (int i = 0; i < m; ++i) {
        cnt[i] = 0;
      }
      for (int i = 0; i < n; ++i) {
        ++cnt[rk[i]];
      }
      for (int i = 1; i < m; ++i) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; ~i; --i) {
        sa[--cnt[rk[id[i]]]] = id[i];
      }
    };

    auto cmp = [&](int x, int y, int l) {
      if (id[x] != id[y]) return false;
      x += l, y += l;
      return x < n && y < n && id[x] == id[y];
    };
  
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
      rk.swap(id);
			p = 1, rk[sa[0]] = 0;
			for (int i = 1; i < n; ++i) {
				if (!cmp(sa[i - 1], sa[i], l)) {
					++p;
				}
				rk[sa[i]] = p - 1;
			}
		}

    s.push_back(-1);
    h[0] = 0;
    for (int i = 0, k = 0; i < n; ++i) {
      if (!rk[i]) {
        continue;
      }
      if (k) {
        --k;
      }
      while (s[i + k] == s[sa[rk[i] - 1] + k]) {
        ++k;
      }
      h[rk[i]] = k;
    }
	}

  std::vector<int> get_id() const {
    return sa;
  }

  std::vector<int> get_height() const {
    return h;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::reverse(s.begin(), s.end());

  suffix_array SA(s);
  auto a = SA.get_height(), p = SA.get_id();
  a.insert(a.begin(), 0), p.insert(p.begin(), n);
  int k = std::find(p.begin(), p.end(), 0) - p.begin();
  p.erase(p.begin() + k);
  if (k < n) {
    a[k + 1] = std::min(a[k + 1], a[k]);
  }
  a.erase(a.begin() + k);
  for (int i = 0; i < n; ++i) {
    --p[i];
  }

  std::vector<int> c0(n + 1);
  for (int i = 0; i < n; ++i) {
    if (s[i] == '0') {
      c0[i + 1] = c0[i] + 1;
    }
  }
  std::vector<int> c9(n + 1);
  for (int i = 0; i < n; ++i) {
    if (s[i] == '9') {
      c9[i + 1] = c9[i] + 1;
    }
  }

  std::vector<int> l(n), r(n, n);
  std::vector<int> sta;
  for (int i = 1; i < n; ++i) {
    while (!sta.empty() && a[sta.back()] >= a[i]) {
      r[sta.back()] = i;
      sta.pop_back();
    }
    if (!sta.empty()) {
      l[i] = sta.back();
    }
    sta.push_back(i);
  }

  long long ans = 0;
  for (int v = 0; v < 9; ++v) {
    std::vector<std::vector<std::pair<int, int>>> Q(n + 1);
    for (int i = 1; i < n; ++i) {
      if (i - l[i] < r[i] - i) {
        for (int j = l[i]; j < i; ++j) {
          if (s[p[j]] - '0' == v) {
            Q[r[i]].emplace_back(c9[p[j]], a[i] + 1);
            Q[i].emplace_back(c9[p[j]], -a[i] - 1);
          }
        }
      } else {
        for (int j = i; j < r[i]; ++j) {
          if (s[p[j]] - '0' == v) {
            Q[i].emplace_back(c9[p[j]], a[i] + 1);
            Q[l[i]].emplace_back(c9[p[j]], -a[i] - 1);
          }
        }
      }
    }
    fenwick_tree<int> T(n);
    fenwick_tree<long long> Ti(n);
    int tot = 0;
    for (int i = 0; i <= n; ++i) {
      for (auto [x, d] : Q[i]) {
        ans += (Ti.query(x) + 1ll * (tot - T.query(x)) * (x + 1)) * d;
      }
      if (i < n && s[p[i]] - '0' == v + 1) {
        Ti.modify(c0[p[i]], c0[p[i]] + 1);
        T.modify(c0[p[i]], 1);
        ++tot;
      }
    }
  }
  for (int v = 0; v < 9; ++v) {
    std::vector<std::vector<std::pair<int, int>>> Q(n + 1);
    for (int i = 1; i < n; ++i) {
      if (i - l[i] < r[i] - i) {
        for (int j = l[i]; j < i; ++j) {
          if (s[p[j]] - '0' == v + 1) {
            Q[r[i]].emplace_back(c0[p[j]], a[i] + 1);
            Q[i].emplace_back(c0[p[j]], -a[i] - 1);
          }
        }
      } else {
        for (int j = i; j < r[i]; ++j) {
          if (s[p[j]] - '0' == v + 1) {
            Q[i].emplace_back(c0[p[j]], a[i] + 1);
            Q[l[i]].emplace_back(c0[p[j]], -a[i] - 1);
          }
        }
      }
    }
    fenwick_tree<int> T(n);
    fenwick_tree<long long> Ti(n);
    int tot = 0;
    for (int i = 0; i <= n; ++i) {
      for (auto [x, d] : Q[i]) {
        ans += (Ti.query(x) + 1ll * (tot - T.query(x)) * (x + 1)) * d;
      }
      if (i < n && s[p[i]] - '0' == v) {
        Ti.modify(c9[p[i]], c9[p[i]] + 1);
        T.modify(c9[p[i]], 1);
        ++tot;
      }
    }
  }
  std::cout << ans << "\n";
}
