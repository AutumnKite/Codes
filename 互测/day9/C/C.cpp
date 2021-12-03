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

struct node {
  int max, cnt;

  node() : max(-1), cnt() {}

  node(int t_max, int t_cnt) : max(t_max), cnt(t_cnt) {}

  node operator+(const node &rhs) const {
    return node(std::max(max, rhs.max), cnt + rhs.cnt);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> edge(n);
  for (auto &[u, v] : edge) {
    std::cin >> u >> v;
    --u, --v;
  }

  std::vector<std::vector<bool>> ok(n, std::vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      graph G(n);
      for (int k = i; k <= j; ++k) {
        G.add_edge(edge[k].first, edge[k].second);
      }
      ok[i][j] = G.check();
    }
  }

  int q;
  std::cin >> q;
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    --l;
    int ans = 0;
    for (int i = l; i < r; ++i) {
      for (int j = i; j < r; ++j) {
        ans += ok[i][j];
      }
    }
    std::cout << ans << "\n";
  }
}
