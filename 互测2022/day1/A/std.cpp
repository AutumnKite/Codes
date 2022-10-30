#include <bits/stdc++.h>

template<typename Val,
         typename VV = std::plus<>,
         typename Tag = Val,
         typename VT = std::plus<>,
         typename TT = std::plus<>,
         typename Comp = std::less<>>
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
  Comp comp;

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

  size_type lower_bound(size_type u, size_type l, size_type r, 
                        size_type L, size_type R,
                        Val &pre, const Val &v) {
    if (L <= l && r <= R) {
      const Val &tmp = fun_vv(pre, val[u]);
      if (comp(tmp, v)) {
        pre = tmp;
        return r;
      }
    }
    if (l + 1 == r) {
      return l;
    }
    size_type mid = (l + r) >> 1;
    down(u);
    if (R <= mid) {
      return lower_bound(u << 1, l, mid, L, R, pre, v);
    } else if (L >= mid) {
      return lower_bound(u << 1 | 1, mid, r, L, R, pre, v);
    } else {
      size_type res = lower_bound(u << 1, l, mid, L, R, pre, v);
      if (res < mid) {
        return res;
      } else {
        return lower_bound(u << 1 | 1, mid, r, L, R, pre, v);
      }
    }
  }

  size_type upper_bound(size_type u, size_type l, size_type r, 
                        size_type L, size_type R,
                        Val &pre, const Val &v) {
    if (L <= l && r <= R) {
      const Val &tmp = fun_vv(pre, val[u]);
      if (!comp(v, tmp)) {
        pre = tmp;
        return r;
      }
    }
    if (l + 1 == r) {
      return l;
    }
    size_type mid = (l + r) >> 1;
    down(u);
    if (R <= mid) {
      return upper_bound(u << 1, l, mid, L, R, pre, v);
    } else if (L >= mid) {
      return upper_bound(u << 1 | 1, mid, r, L, R, pre, v);
    } else {
      size_type res = upper_bound(u << 1, l, mid, L, R, pre, v);
      if (res < mid) {
        return res;
      } else {
        return upper_bound(u << 1 | 1, mid, r, L, R, pre, v);
      }
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

  size_type lower_bound(size_type l, size_type r, Val E, const Val &v) {
    return lower_bound(1, 0, n, l, r, E, v);
  }

  size_type upper_bound(size_type l, size_type r, Val E, const Val &v) {
    return upper_bound(1, 0, n, l, r, E, v);
  }
};

struct node {
  int sum, lmx, lxp, rmx, rxp, mx, xpl, xpr, lmn, lnp, rmn, rnp, mn, npl, npr;

  node() = default;

  node(int v, int i) {
    sum = lmx = rmx = mx = lmn = rmn = mn = v;
    rxp = xpl = rnp = npl = i;
    lxp = xpr = lnp = npr = i + 1;
  }

  node operator+(const node &b) const {
    node r;
    r.sum = sum + b.sum;
    if (lmx > sum + b.lmx)
      r.lmx = lmx, r.lxp = lxp;
    else
      r.lmx = sum + b.lmx, r.lxp = b.lxp;
    if (b.rmx > rmx + b.sum)
      r.rmx = b.rmx, r.rxp = b.rxp;
    else
      r.rmx = rmx + b.sum, r.rxp = rxp;
    if (mx > b.mx)
      r.mx = mx, r.xpl = xpl, r.xpr = xpr;
    else
      r.mx = b.mx, r.xpl = b.xpl, r.xpr = b.xpr;
    if (rmx + b.lmx > r.mx)
      r.mx = rmx + b.lmx, r.xpl = rxp, r.xpr = b.lxp;
    if (lmn < sum + b.lmn)
      r.lmn = lmn, r.lnp = lnp;
    else
      r.lmn = sum + b.lmn, r.lnp = b.lnp;
    if (b.rmn < rmn + b.sum)
      r.rmn = b.rmn, r.rnp = b.rnp;
    else
      r.rmn = rmn + b.sum, r.rnp = rnp;
    if (mn < b.mn)
      r.mn = mn, r.npl = npl, r.npr = npr;
    else
      r.mn = b.mn, r.npl = b.npl, r.npr = b.npr;
    if (rmn + b.lmn < r.mn)
      r.mn = rmn + b.lmn, r.npl = rnp, r.npr = b.lnp;
    return r;
  }

  void update() {
    sum *= -1, lmx *= -1, lmn *= -1, rmx *= -1, rmn *= -1, mx *= -1, mn *= -1;
    std::swap(lmx, lmn), std::swap(lxp, lnp);
    std::swap(rmx, rmn), std::swap(rxp, rnp);
    std::swap(mx, mn), std::swap(xpl, npl), std::swap(xpr, npr);
  }

  node operator+(int d) const {
    if (d == 1) {
      node res = *this;
      res.update();
      return res;
    }
    return *this;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<int> cnt0(n + 1), cnt1(n + 1);
  for (int i = 0; i < n; ++i) {
    cnt0[i + 1] = cnt0[i] + (s[i] == '0');
    cnt1[i + 1] = cnt1[i] + (s[i] == '1');
  }
  std::vector<int> ans(n);
  for (int i = 0; i <= n; ++i) {
    ans[0] = std::max(ans[0], cnt0[i] + cnt1[n] - cnt1[i]);
  }
  for (int v = 0; v < 2; ++v) {
    std::vector<node> tmp(n);
    for (int i = 0; i < n; ++i) {
      tmp[i] = node(s[i] == '0' + v ? -1 : 1, i);
    }
    lazy_seg_tree<node, std::plus<>, int, std::plus<>, std::bit_xor<>> T(tmp);
    int now = 0;
    for (int k = 1; k <= n + 1; ++k) {
      node tmp = T.query(0, n);
			now += tmp.lmx;
			T.modify(0, tmp.lxp, 1);
      if (k > 2) {
        ans[k - 2] = std::max(ans[k - 2], now + (v == 0 ? cnt0[n] : cnt1[n]));
      }
    }
  }
  std::cout << ans[0];
  for (int i = 1; i < n; ++i) {
    ans[i] = std::max(ans[i], ans[i - 1]);
    std::cout << " " << ans[i];
  }
  std::cout << "\n";
}
