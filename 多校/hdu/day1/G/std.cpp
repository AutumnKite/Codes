#include <bits/stdc++.h>

class disjoint_set {
public:
  typedef std::size_t size_type;

protected:
  std::vector<size_type> fa;

public:
  disjoint_set(size_type n = 0) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  size_type find(size_type x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
  }

  bool merge(size_type x, size_type y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    fa[y] = x;
    return true;
  }
};

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

class tree {
  int n, lg;
  std::vector<int> a;
  std::vector<std::vector<int>> E;
  std::vector<std::vector<int>> fa;
  std::vector<int> size;
  int idx0, idx1;
  std::vector<int> dfn, dfne;
  std::vector<std::vector<int>> st;

  void dfs(int u) {
    dfn[u] = idx0++;
    st[0][idx1] = u;
    dfne[u] = idx1++;
    for (int v : E[u]) {
      dfs(v);
      size[u] += size[v];
      st[0][idx1] = u;
      dfne[u] = idx1++;
    }
  }

public:
  tree(std::vector<int> t_a, std::vector<int> t_fa)
      : n(t_a.size()), lg(std::__lg(n)), a(t_a), E(n),
        fa(lg + 1, std::vector<int>(n, -1)), size(n, 1), 
        idx0(), idx1(), dfn(n), dfne(n),
        st(lg + 2, std::vector<int>(2 * n - 1)) {
    fa[0] = t_fa;
    for (int u = n - 2; u >= 0; --u) {
      E[fa[0][u]].push_back(u);
    }
    for (int i = 0; i < lg; ++i) {
      for (int u = 0; u < n; ++u) {
        if (fa[i][u] != -1) {
          fa[i + 1][u] = fa[i][fa[i][u]];
        }
      }
    }
    dfs(n - 1);
    for (int i = 0; i <= lg; ++i) {
      for (int j = 0; j + (1 << (i + 1)) < 2 * n; ++j) {
        st[i + 1][j] = std::max(st[i][j], st[i][j + (1 << i)]);
      }
    }
  }

  int LCA(int u, int v) const {
    int l = dfne[u], r = dfne[v];
    if (l > r) {
      std::swap(l, r);
    }
    ++r;
    int t = std::__lg(r - l);
    return std::max(st[t][l], st[t][r - (1 << t)]);
  }

  int jump(int u, int w) const {
    for (int i = lg; i >= 0; --i) {
      if (fa[i][u] != -1 && a[fa[i][u]] <= w) {
        u = fa[i][u];
      }
    }
    return u;
  }

  int DFN(int x) const {
    return dfn[x];
  }

  int END(int x) const {
    return dfn[x] + size[x];
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int> c(n);
    std::vector<std::vector<int>> pos(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> c[i];
      --c[i];
      pos[c[i]].push_back(i);
    }
    std::vector<long long> a(n);
    std::vector<int> tmp(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> tmp[i];
    }
    std::vector<std::tuple<int, int, int>> edge;
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      std::cin >> u >> v >> w;
      --u, --v;
      edge.emplace_back(w, u, v);
    }
    std::sort(edge.begin(), edge.end());

    disjoint_set D(2 * n - 1);
    std::vector<int> fa(2 * n - 1, -1);
    std::vector<int> val(2 * n - 1);
    int idx = n;
    for (auto p : edge) {
      int w = std::get<0>(p), u = std::get<1>(p), v = std::get<2>(p);
      if (D.find(u) != D.find(v)) {
        val[idx] = w;
        fa[D.find(u)] = idx;
        fa[D.find(v)] = idx;
        D.merge(idx, u);
        D.merge(idx, v);
        idx++;
      }
    }
    tree T(val, fa);
    fenwick_tree<long long> S(2 * n - 1);
    std::vector<long long> d(2 * n - 1);

    auto add = [&](int x, int y, int op) {
      std::vector<std::pair<int, int>> Q;
      for (int u : pos[c[x]]) {
        Q.emplace_back(T.LCA(u, x), u);
      }
      std::sort(Q.begin(), Q.end());
      int k = Q.size();
      long long old = a[x], now = a[x] + y, lst = 0;
      for (int i = 0; i < k; ++i) {
        old = std::max(old, a[Q[i].second]);
        now = std::max(now, a[Q[i].second]);
        if (i + 1 == k || Q[i + 1].first != Q[i].first) {
          if (op) {
            S.modify(T.DFN(Q[i].first), now - old - lst);
          } else {
            d[T.DFN(Q[i].first)] += now - old - lst;
          }
          lst = now - old;
        }
      }
      a[x] += y;
    };

    for (int i = 0; i < n; ++i) {
      add(i, tmp[i], 0);
    }
    for (int i = 0; i < 2 * n - 1; ++i) {
      S.modify(i, d[i]);
    }
    while (q--) {
      int op, x, y;
      std::cin >> op >> x >> y;
      --x;
      if (op == 0) {
        add(x, y, 1);
      } else {
        int u = T.jump(x, y);
        std::cout << S.query(T.END(u)) - S.query(T.DFN(u)) << "\n";
      }
    }
  }
}
