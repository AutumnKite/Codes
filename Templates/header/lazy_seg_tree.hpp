#ifndef MYH_LAZY_SEG_TREE_HPP
#define MYH_LAZY_SEG_TREE_HPP 1

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>

namespace myh {

template<typename _Val,
         typename _VV = std::plus<>,
         typename _Tag = _Val,
         typename _VT = std::plus<>,
         typename _TT = std::plus<>>
class lazy_seg_tree {
public:
  typedef std::size_t size_type;

private:
  static size_type enlarge(size_type n) {
    size_type res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const size_type n, en;

  _VV fun_vv;
  _VT fun_vt;
  _TT fun_tt;

  std::vector<_Val> val;
  std::vector<_Tag> tag;

  void up(size_type u) {
    val[u] = fun_vv(val[u << 1], val[u << 1 | 1]);
  }

  void apply(size_type u, const _Tag &v) {
    val[u] = fun_vt(val[u], v);
    tag[u] = fun_tt(tag[u], v);
  }

  void down(size_type u) {
    apply(u << 1, tag[u]);
    apply(u << 1 | 1, tag[u]);
    tag[u] = _Tag();
  }

  template<typename T>
  void build(size_type u, size_type l, size_type r, 
         const std::vector<T> &a) {
    if (l + 1 == r) {
      val[u] = _Val(a[l]);
      return;
    }
    size_type mid = (l + r) >> 1;
    build(u << 1, l, mid, a);
    build(u << 1 | 1, mid, r, a);
    up(u);
  }

  void modify(size_type u, size_type l, size_type r, 
        size_type x, const _Val &v) {
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
        size_type L, size_type R, const _Tag &v) {
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

  _Val query(size_type u, size_type l, size_type r, 
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

  void modify(size_type x, const _Val &v) {
    modify(1, 0, n, x, v);
  }

  void modify(size_type l, size_type r, const _Tag &v) {
    if (l < r) {
      modify(1, 0, n, l, r, v);
    }
  }

  _Val query(size_type l, size_type r) {
    if (l < r) {
      return query(1, 0, n, l, r);
    } else {
      return _Val();
    }
  }
};

} // namespace myh

#endif // MYH_LAZY_SEG_TREE_HPP
