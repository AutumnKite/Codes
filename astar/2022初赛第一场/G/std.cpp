#include <bits/stdc++.h>

template<typename Val, 
         typename VV = std::plus<Val>,
         typename Tag = Val, 
         typename VT = std::plus<Val>>
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> fa(n, -1);
  std::vector<std::vector<int>> E(n);
  for (int i = 1; i < n; ++i) {
    std::cin >> fa[i];
    --fa[i];
    E[fa[i]].push_back(i);
  }

  std::vector<int> dfn(n), end(n);
  int idx = 0;

  std::function<void(int)> dfs = [&](int u) -> void {
    dfn[u] = idx++;
    for (int v : E[u]) {
      dfs(v);
    }
    end[u] = idx;
  };

  dfs(0);

  std::map<int, dynamic_seg_tree<int>> T;
  int q;
  std::cin >> q;
  while (q--) {
    int op, x, y;
    std::cin >> op >> x >> y;
    --x, --y;
    auto it = T.find(y);
    if (it == T.end()) {
      it = T.emplace(y, dynamic_seg_tree<int>(0, n)).first;
    }
    if (op == 1) {
      it->second.modify(dfn[x], 1);
    } else {
      std::cout << it->second.query(dfn[x], end[x]) << "\n";
    }
  }
}
