#include <bits/stdc++.h>

template<typename Val, typename VV = std::plus<Val>>
class dynamic_tree {
public:
  typedef std::size_t size_type;

protected:
  VV fun;

  struct node {
    node *fa, *ls, *rs;
    Val v, sv;
    bool rev;

    node() : fa(), ls(), rs(), v(), sv(), rev() {}

    node(const Val &t_v) : fa(), ls(), rs(), v(t_v), sv(v), rev() {}

    node *&son(bool d) {
      if (!d) {
        return ls;
      } else {
        return rs;
      }
    }

    bool is_root() const {
      return !fa || (fa->ls != this && fa->rs != this);
    }

    bool which() const {
      return fa->rs == this;
    }

    void change(bool d, node *v) {
      if (v) {
        v->fa = this;
      }
      son(d) = v;
    }
  };

  std::vector<node *> nd;

  void up(node *u) {
    u->sv = u->v;
    if (u->ls) {
      u->sv = fun(u->sv, u->ls->sv);
    }
    if (u->rs) {
      u->sv = fun(u->sv, u->rs->sv);
    }
  }

  void apply_rev(node *u) {
    if (u) {
      std::swap(u->ls, u->rs);
      u->rev = !u->rev;
    }
  }

  void down(node *u) {
    if (u->rev) {
      apply_rev(u->ls);
      apply_rev(u->rs);
      u->rev = false;
    }
  }

  void rotate(node *u) {
    node *v = u->fa;
    bool k = u->which();
    v->change(k, u->son(!k));
    if (!v->is_root()) {
      v->fa->change(v->which(), u);
    } else {
      u->fa = v->fa;
    }
    u->change(!k, v);
    up(v), up(u);
  }

  void splay(node *u) {
    static std::vector<node *> sta;
    sta.push_back(u);
    for (node *i = u; !i->is_root(); i = i->fa) {
      sta.push_back(i->fa);
    }
    while (!sta.empty()) {
      down(sta.back());
      sta.pop_back();
    }
    while (!u->is_root()) {
      node *v = u->fa;
      if (v->is_root()) {
        rotate(u);
        break;
      }
      if (u->which() == v->which()) {
        rotate(v);
      } else {
        rotate(u);
      }
      rotate(u);
    }
  }

  void access(node *u) {
    node *v = nullptr;
    while (u) {
      splay(u);
      u->son(1) = v;
      up(u);
      v = u, u = u->fa;
    }
  }

  void make_root(node *u) {
    access(u);
    splay(u);
    apply_rev(u);
  }

  node *find_root(node *u) {
    access(u);
    splay(u);
    while (u->ls) {
      down(u);
      u = u->ls;
    }
    splay(u);
    return u;
  }

  void split(node *u, node *v) {
    make_root(u);
    access(v);
    splay(v);
  }

public:
  dynamic_tree(size_type n = 0) : nd(n) {
    for (size_type i = 0; i < n; ++i) {
      nd[i] = new node();
    }
  }

  dynamic_tree(const std::vector<Val> &a) : nd(a.size()) {
    for (size_type i = 0; i < a.size(); ++i) {
      nd[i] = new node(a[i]);
    }
  }

  void link(size_type x, size_type y) {
    node *u = nd[x], *v = nd[y];
    make_root(u);
    if (find_root(v) != u) {
      u->fa = v;
    }
  }

  void cut(size_type x, size_type y) {
    node *u = nd[x], *v = nd[y];
    make_root(u);
    if (find_root(v) == u && v->fa == u && !v->ls) {
      u->rs = nullptr;
      v->fa = nullptr;
      up(u);
    }
  }

  void modify(size_type x, const Val &a) {
    node *u = nd[x];
    splay(u);
    u->v = a;
    up(u);
  }

  Val query(size_type x, size_type y) {
    node *u = nd[x], *v = nd[y];
    split(u, v);
    return v->sv;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int &v : a) {
    std::cin >> v;
  }
  
  dynamic_tree<int, std::bit_xor<int>> T(a);
  while (q--) {
    int op;
    std::cin >> op;
    if (op == 3) {
      int x, v;
      std::cin >> x >> v;
      --x;
      T.modify(x, v);
    } else {
      int x, y;
      std::cin >> x >> y;
      --x, --y;
      if (op == 0) {
        std::cout << T.query(x, y) << "\n";
      } else if (op == 1) {
        T.link(x, y);
      } else if (op == 2) {
        T.cut(x, y);
      }
    }
  }
}
