#ifndef MYH_DYNAMIC_SEG_TREE_HPP
#define MYH_DYNAMIC_SEG_TREE_HPP 1

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>

namespace myh {

template<typename Val, 
         typename VV = std::plus<>,
         typename Tag = Val, 
         typename VT = std::plus<>>
class dynamic_seg_tree {
public:
  typedef std::size_t size_type;

  const Val E;

protected:
  const size_type nl, nr;

  VV fun_vv;
  VT fun_vt;

  struct node {
    node *ls, *rs;
    Val v;

    node(const Val &_v) : ls(nullptr), rs(nullptr), v(_v) {}
  };

  node *rt;
  
  void up(node *u) {
    u->v = fun_vv(u->ls == nullptr ? E : u->ls->v, 
                  u->rs == nullptr ? E : u->rs->v);
  }

  void modify(node *&u, size_type l, size_type r, 
              size_type x, const Val &v) {
    if (u == nullptr) {
      u = new node(E);
    }
    if (l + 1 == r) {
      u->v = v;
      return;
    }
    size_type mid = l + ((r - l) >> 1);
    if (x < mid) {
      modify(u->ls, l, mid, x, v);
    } else {
      modify(u->rs, mid, r, x, v);
    }
    up(u);
  }

  void add(node *&u, size_type l, size_type r, 
           size_type x, const Tag &v) {
    if (u == nullptr) {
      u = new node(E);
    }
    if (l + 1 == r) {
      u->v = fun_vt(u->v, v);
      return;
    }
    size_type mid = l + ((r - l) >> 1);
    if (x < mid) {
      add(u->ls, l, mid, x, v);
    } else {
      add(u->rs, mid, r, x, v);
    }
    up(u);
  }

  Val query(node *u, size_type l, size_type r, 
            size_type L, size_type R) const {
    if (u == nullptr) {
      return E;
    }
    if (L <= l && r <= R) {
      return u->v;
    }
    size_type mid = l + ((r - l) >> 1);
    if (R <= mid) {
      return query(u->ls, l, mid, L, R);
    } else if (L >= mid) {
      return query(u->rs, mid, r, L, R);
    } else {
      return fun_vv(query(u->ls, l, mid, L, R),
                    query(u->rs, mid, r, L, R));
    }
  }

public:
  dynamic_seg_tree(size_type _nl, size_type _nr)
  : E(), nl(_nl), nr(_nr), rt(nullptr) {}

  dynamic_seg_tree(size_type _nl, size_type _nr, const Val &_E)
  : E(_E), nl(_nl), nr(_nr), rt(nullptr) {}

  void modify(size_type x, const Val &v) {
    modify(rt, nl, nr, x, v);
  }

  void add(size_type x, const Tag &v) {
    add(rt, nl, nr, x, v);
  }

  Val query(size_type l, size_type r) const {
    if (l < r) {
      return query(rt, nl, nr, l, r);
    } else {
      return E;
    }
  }
};

} // namespace myh

#endif // MYH_DYNAMIC_SEG_TREE_HPP
