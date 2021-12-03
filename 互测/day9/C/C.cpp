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

  bool connected(size_type x, size_type y) {
    node *u = nd[x], *v = nd[y];
    return find_root(u) == find_root(v);
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

struct info {
  int max, cnt;

  info() : max(-1), cnt(0) {}

  info(int t_max, int t_cnt) : max(t_max), cnt(t_cnt) {}

  info operator+(const info &rhs) const {
    return info(std::max(max, rhs.max), cnt + rhs.cnt);
  }
};

const int INF = std::numeric_limits<int>::max() / 2;

struct node {
  int min, c;
  long long sum;
};

class segtree {
  constexpr static int enlarge(int n) {
    int res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const int n, en;

  std::vector<node> val;
  std::vector<int> tag1, tag2;

  void up(int u) {
    int ls = u << 1, rs = u << 1 | 1;
    val[u].sum = val[ls].sum + val[rs].sum;
    val[u].min = std::min(val[ls].min, val[rs].min);
    val[u].c = 0;
    if (val[u].min == val[ls].min) {
      val[u].c += val[ls].c;
    }
    if (val[u].min == val[rs].min) {
      val[u].c += val[rs].c;
    }
  }

  void apply1(int u, int v) {
    val[u].min += v;
    tag1[u] += v;
  }

  void apply2(int u, int v) {
    val[u].sum += 1ll * val[u].c * v;
    tag2[u] += v;
  }

  void down(int u) {
    int ls = u << 1, rs = u << 1 | 1;
    if (tag1[u]) {
      apply1(ls, tag1[u]);
      apply1(rs, tag1[u]);
      tag1[u] = 0;
    }
    if (tag2[u]) {
      if (val[ls].min == val[u].min) {
        apply2(ls, tag2[u]);
      }
      if (val[rs].min == val[u].min) {
        apply2(rs, tag2[u]);
      }
      tag2[u] = 0;
    }
  }

  void build(int u, int l, int r) {
    if (l + 1 == r) {
      val[u].min = 0;
      val[u].c = 1;
      val[u].sum = 0;
      return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid, r);
    up(u);
  }

  void modify1(int u, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) {
      apply1(u, v);
      return;
    }
    int mid = (l + r) >> 1;
    down(u);
    if (L < mid) {
      modify1(u << 1, l, mid, L, R, v);
    }
    if (mid < R) {
      modify1(u << 1 | 1, mid, r, L, R, v);
    }
    up(u);
  }

  void modify2(int u, int l, int r, int L, int R, int v, int need) {
    if (val[u].min > need) {
      return;
    }
    if (L <= l && r <= R) {
      apply2(u, v);
      return;
    }
    int mid = (l + r) >> 1;
    down(u);
    if (L < mid) {
      modify2(u << 1, l, mid, L, R, v, need);
    }
    if (mid < R) {
      modify2(u << 1 | 1, mid, r, L, R, v, need);
    }
    up(u);
  }

  int query_min(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
      return val[u].min;
    }
    int mid = (l + r) >> 1;
    down(u);
    if (R <= mid) {
      return query_min(u << 1, l, mid, L, R);
    } else if (L >= mid) {
      return query_min(u << 1 | 1, mid, r, L, R);
    } else {
      return std::min(query_min(u << 1, l, mid, L, R),
                      query_min(u << 1 | 1, mid, r, L, R));
    }
  }

  long long query_sum(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
      return val[u].sum;
    }
    int mid = (l + r) >> 1;
    down(u);
    long long res = 0;
    if (L < mid) {
      res += query_sum(u << 1, l, mid, L, R);
    }
    if (mid < R) {
      res += query_sum(u << 1 | 1, mid, r, L, R);
    }
    return res;
  }

public:
  segtree(int t_n)
  : n(t_n), en(enlarge(n)), val(en << 1), tag1(en << 1), tag2(en << 1) {
    if (n) {
      build(1, 0, n);
    }
  }

  void modify1(int l, int r, int v) {
    if (l < r) {
      modify1(1, 0, n, l, r, v);
    }
  }

  void modify2(int l, int r, int v, int need) {
    if (l < r) {
      modify2(1, 0, n, l, r, v, need);
    }
  }

  int query_min(int l, int r) {
    if (l < r) {
      return query_min(1, 0, n, l, r);
    } else {
      return INF;
    }
  }

  long long query_sum(int l, int r) {
    if (l < r) {
      return query_sum(1, 0, n, l, r);
    } else {
      return 0;
    }
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
  int q;
  std::cin >> q;
  std::vector<std::vector<std::pair<int, int>>> Q(n);
  for (int i = 0; i < q; ++i) {
    int l, r;
    std::cin >> l >> r;
    --l;
    Q[l].emplace_back(r, i);
  }

  std::vector<int> deg(n);
  dynamic_tree<info> T(n * 2);
  int first = n, second = n;
  int pos = n, cnt = 0;

  auto add_deg = [&](int u, int d) {
    cnt -= deg[u] > 2;
    deg[u] += d;
    cnt += deg[u] > 2;
    T.modify(u, info(-1, deg[u] > 2));
  };

  segtree S(n);
  std::vector<int> lst(n, n);
  std::vector<long long> ans(q);
  for (int i = n - 1; i >= 0; --i) {
    auto [u, v] = edge[i];
    if (T.connected(u, v)) {
      auto tmp = T.query(u, v);
      if (tmp.max < first) {
        second = first;
        first = tmp.max;
      } else if (tmp.max < second) {
        second = tmp.max;
      }
      T.cut(edge[tmp.max].first, n + tmp.max);
      T.cut(edge[tmp.max].second, n + tmp.max);
    }
    T.modify(n + i, info(i, 0));
    T.link(u, n + i);
    T.link(v, n + i);
    add_deg(u, 1);
    add_deg(v, 1);
    while (pos > first && cnt - T.query(edge[first].first,
                                    edge[first].second).cnt > 0) {
      --pos;
      add_deg(edge[pos].first, -1);
      add_deg(edge[pos].second, -1);
    }
    S.modify1(i, n, -1);
    S.modify1(i, lst[u], 1);
    S.modify1(i, lst[v], 1);
    lst[u] = lst[v] = i;
    int l = first, r = std::min(second, pos);
    S.modify2(l, r, 1, 0);
    for (auto [x, id] : Q[i]) {
      ans[id] = S.query_sum(i, x);
    }
  }
  
  for (int i = 0; i < q; ++i) {
    std::cout << ans[i] << "\n";
  }
}
