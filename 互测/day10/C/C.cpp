#include <bits/stdc++.h>

template<typename Val,
         typename VV = std::plus<>,
         typename Tag = Val,
         typename VT = std::plus<>,
         typename TT = std::plus<>>
class lazy_seg_tree {
public:
  typedef std::size_t size_type;

private:
  constexpr static size_type enlarge(size_type n) {
    size_type res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const size_type n, en;

  VV fun_vv;
  VT fun_vt;
  TT fun_tt;

  std::vector<Val> val;
  std::vector<Tag> tag;

  void up(size_type u) {
    val[u] = fun_vv(val[u << 1], val[u << 1 | 1]);
  }

  void apply(size_type u, const Tag &v) {
    val[u] = fun_vt(val[u], v);
    tag[u] = fun_tt(tag[u], v);
  }

  void down(size_type u) {
    apply(u << 1, tag[u]);
    apply(u << 1 | 1, tag[u]);
    tag[u] = Tag();
  }

  template<typename T>
  void build(size_type u, size_type l, size_type r, 
             const std::vector<T> &a) {
    if (l + 1 == r) {
      val[u] = Val(a[l]);
      return;
    }
    size_type mid = (l + r) >> 1;
    build(u << 1, l, mid, a);
    build(u << 1 | 1, mid, r, a);
    up(u);
  }

  void modify(size_type u, size_type l, size_type r, 
              size_type x, const Val &v) {
    if (l + 1 == r) {
      val[u] = v;
      return;
    }
    size_type mid = (l + r) >> 1;
    down(u);
    if (x < mid) {
      modify(u << 1, l, mid, x, v);
    } else {
      modify(u << 1 | 1, mid, r, x, v);
    }
    up(u);
  }

  void modify(size_type u, size_type l, size_type r, 
              size_type L, size_type R, const Tag &v) {
    if (L <= l && r <= R) {
      apply(u, v);
      return;
    }
    size_type mid = (l + r) >> 1;
    down(u);
    if (L < mid) {
      modify(u << 1, l, mid, L, R, v);
    }
    if (mid < R) {
      modify(u << 1 | 1, mid, r, L, R, v);
    }
    up(u);
  }

  Val query(size_type u, size_type l, size_type r, 
            size_type L, size_type R) {
    if (L <= l && r <= R) {
      return val[u];
    }
    size_type mid = (l + r) >> 1;
    down(u);
    if (R <= mid) {
      return query(u << 1, l, mid, L, R);
    } else if (L >= mid) {
      return query(u << 1 | 1, mid, r, L, R);
    } else {
      return fun_vv(query(u << 1, l, mid, L, R), 
                    query(u << 1 | 1, mid, r, L, R));
    }
  }

public:
  lazy_seg_tree() : lazy_seg_tree(0) {}

  lazy_seg_tree(size_type _n)
  : n(_n), en(enlarge(n)), val(en << 1), tag(en << 1) {}

  template<typename T>
  lazy_seg_tree(const std::vector<T> &a)
  : n(a.size()), en(enlarge(n)), val(en << 1), tag(en << 1) {
    if (n) {
      build(1, 0, n, a);
    }
  }

  size_type size() const {
    return n;
  }

  void modify(size_type x, const Val &v) {
    modify(1, 0, n, x, v);
  }

  void modify(size_type l, size_type r, const Tag &v) {
    if (l < r) {
      modify(1, 0, n, l, r, v);
    }
  }

  Val query(size_type l, size_type r) {
    if (l < r) {
      return query(1, 0, n, l, r);
    } else {
      return Val();
    }
  }
};

template<typename T>
struct min {
  const T &operator()(const T &a, const T &b) const {
    return std::min(a, b);
  }
};

struct node {
  int mn, c;
  unsigned long long v;

  node() : mn(), c(), v() {}

  node(int x) : mn(x), c(1), v() {}

  node operator+(const node &rhs) const {
    node res;
    res.mn = std::min(mn, rhs.mn);
    res.c = (mn == res.mn ? c : 0) + (rhs.mn == res.mn ? rhs.c : 0);
    res.v = v + rhs.v;
    return res;
  }

  node operator+(unsigned long long d) const {
    node res = *this;
    res.v += d * c;
    return res;
  }
};

class tree {
public:
  typedef std::size_t size_type;

private:
  constexpr static size_type enlarge(size_type n) {
    size_type res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const size_type n, en;

  std::vector<node> val;
  std::vector<unsigned long long> tag;

  void up(size_type u) {
    val[u] = val[u << 1] + val[u << 1 | 1];
  }

  void apply(size_type u, unsigned long long v) {
    val[u] = val[u] + v;
    tag[u] = tag[u] + v;
  }

  void down(size_type u) {
    if (val[u << 1].mn == val[u].mn) {
      apply(u << 1, tag[u]);
    }
    if (val[u << 1 | 1].mn == val[u].mn) {
      apply(u << 1 | 1, tag[u]);
    }
    tag[u] = 0;
  }

  template<typename T>
  void build(size_type u, size_type l, size_type r, 
             const std::vector<T> &a) {
    if (l + 1 == r) {
      val[u] = node(a[l]);
      return;
    }
    size_type mid = (l + r) >> 1;
    build(u << 1, l, mid, a);
    build(u << 1 | 1, mid, r, a);
    up(u);
  }

  void modify(size_type u, size_type l, size_type r, 
              size_type L, size_type R, unsigned long long v, int mn) {
    if (L <= l && r <= R) {
      if (val[u].mn == mn) {
        apply(u, v);
      }
      return;
    }
    size_type mid = (l + r) >> 1;
    down(u);
    if (L < mid) {
      modify(u << 1, l, mid, L, R, v, mn);
    }
    if (mid < R) {
      modify(u << 1 | 1, mid, r, L, R, v, mn);
    }
    up(u);
  }

  node query(size_type u, size_type l, size_type r, 
             size_type L, size_type R) {
    if (L <= l && r <= R) {
      return val[u];
    }
    size_type mid = (l + r) >> 1;
    down(u);
    if (R <= mid) {
      return query(u << 1, l, mid, L, R);
    } else if (L >= mid) {
      return query(u << 1 | 1, mid, r, L, R);
    } else {
      return query(u << 1, l, mid, L, R) + query(u << 1 | 1, mid, r, L, R);
    }
  }

public:
  tree() : tree(0) {}

  tree(size_type _n)
  : n(_n), en(enlarge(n)), val(en << 1), tag(en << 1) {}

  template<typename T>
  tree(const std::vector<T> &a)
  : n(a.size()), en(enlarge(n)), val(en << 1), tag(en << 1) {
    if (n) {
      build(1, 0, n, a);
    }
  }

  size_type size() const {
    return n;
  }

  void modify(size_type l, size_type r, unsigned long long v, int mn) {
    if (l < r) {
      modify(1, 0, n, l, r, v, mn);
    }
  }

  node query(size_type l, size_type r) {
    if (l < r) {
      return query(1, 0, n, l, r);
    } else {
      return node();
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  if (n <= 1000 && q <= 1000) {
    std::vector<std::set<int>> S(n);
    for (int i = 0; i < n; ++i) {
      for (int x = 0; x < q; ++x) {
        S[i].insert(x);
      }
    }
    std::vector<unsigned long long> val(n);
    for (int k = 0; k < q; ++k) {
      int op;
      std::cin >> op;
      if (op == 1) {
        int l, r, x;
        std::cin >> l >> r >> x;
        --l, --x;
        for (int i = l; i < r; ++i) {
          S[i].erase(x);
        }
      } else if (op == 2) {
        int l, r, x;
        std::cin >> l >> r >> x;
        --l, --x;
        for (int i = l; i < r; ++i) {
          S[i].insert(x);
        }
      } else if (op == 3) {
        int l, r;
        unsigned long long v;
        std::cin >> l >> r >> v;
        --l;
        int mn = q;
        for (int i = l; i < r; ++i) {
          mn = std::min(mn, *S[i].begin());
        }
        for (int i = l; i < r; ++i) {
          if (*S[i].begin() == mn) {
            val[i] += v;
          }
        }
      } else {
        int l, r;
        std::cin >> l >> r;
        --l;
        unsigned long long ans = 0;
        for (int i = l; i < r; ++i) {
          ans += val[i];
        }
        std::cout << ans << "\n";
      }
    }
    return 0;
  }

  std::vector<std::map<int, int>> mp(q);

  auto erase = [&](int x, int l, int r) {
    auto it = mp[x].lower_bound(l);
    if (it != mp[x].begin()) {
      auto pr = std::prev(it);
      if (pr->second > r) {
        int t = pr->second;
        pr->second = l;
        mp[x].emplace(r, t);
        return;
      } else if (pr->second > l) {
        pr->second = l;
      }
    }
    while (it != mp[x].end() && it->first < r) {
      int t = it->second;
      it = mp[x].erase(it);
      if (t > r) {
        mp[x].emplace(r, t);
        return;
      }
    }
  };

  auto insert = [&](int x, int l, int r) {
    erase(x, l, r);
    mp[x].emplace(l, r);
  };

  for (int i = 0; i < q; ++i) {
    mp[i].emplace(0, n);
  }
  for (int k = 0; k < q; ++k) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, x;
      std::cin >> l >> r >> x;
      --l, --x;
      erase(x, l, r);
    } else if (op == 2) {
      int l, r, x;
      std::cin >> l >> r >> x;
      --l, --x;
      insert(x, l, r);
    } else {
      lazy_seg_tree<int, min<int>, int, min<int>, min<int>> tmp(n);
      for (int i = 0; i < q; ++i) {
        for (auto [l, r] : mp[i]) {
          tmp.modify(l, r, i - q);
        }
      }
      std::vector<int> val(n);
      for (int i = 0; i < n; ++i) {
        val[i] = tmp.query(i, i + 1) + q;
      }
      tree T(val);
      for (int nk = k; nk < q; ++nk) {
        int nop;
        if (nk == k) {
          nop = op;
        } else {
          std::cin >> nop;
        }
        if (nop == 3) {
          int l, r;
          unsigned long long v;
          std::cin >> l >> r >> v;
          --l;
          T.modify(l, r, v, T.query(l, r).mn);
        } else {
          int l, r;
          std::cin >> l >> r;
          --l;
          std::cout << T.query(l, r).v << "\n";
        }
      }
      break;
    }
  }
}
