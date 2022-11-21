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

  Val query(size_type x) const {
    Val s = E;
    for (; x; x ^= x & -x) {
      s = fun(s, val[x]);
    }
    return s;
  }
};

using i64 = int64_t;
using i128 = __int128_t;

std::ostream &operator<<(std::ostream &out, i128 x) {
  if (x == 0) {
    return out << 0;
  }
  if (x < 0) {
    x = -x;
    out << '-';
  }
  std::string s;
  while (x) {
    s.push_back(x % 10 + '0');
    x /= 10;
  }
  std::reverse(s.begin(), s.end());
  return out << s;
}

struct state {
  int s0;
  i64 s1;
  i128 s2;

  state() : s0(), s1(), s2() {}

  state(int v) : s0(1), s1(v), s2((i64)v * v) {}
  
  state(int s0, i64 s1, i128 s2) : s0(s0), s1(s1), s2(s2) {}

  state operator+(const state &rhs) const {
    return state(s0 + rhs.s0, s1 + rhs.s1, s2 + rhs.s2);
  }

  state operator-(const state &rhs) const {
    return state(s0 - rhs.s0, s1 - rhs.s1, s2 - rhs.s2);
  }

  state operator-() const {
    return state(-s0, -s1, -s2);
  }
};

template<typename Tp>
class tree {
  int n;
  std::vector<std::vector<int>> E;
  std::vector<Tp> a;
  fenwick_tree<Tp> T;
  std::vector<int> sta;
  int idx;
  std::vector<int> fa, dep, size, son, top, dfn;

  void dfs1(int u) {
    for (int v : E[u]) {
      if (v != fa[u]) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v);
        size[u] += size[v];
        if (son[u] == -1 || size[v] > size[son[u]]) {
          son[u] = v;
        }
      }
    }
  }

  void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = idx++;
    if (son[u] != -1) {
      dfs2(son[u], tp);
    }
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs2(v, v);
      }
    }
  }

public:
  tree(int t_n) : n(t_n), E(n), a(n), T(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  void init() {
    fa.assign(n, -1);
    dep.assign(n, 0);
    size.assign(n, 1);
    son.assign(n, -1);
    dfs1(0);
    idx = 0;
    top.assign(n, 0);
    dfn.assign(n, 0);
    dfs2(0, 0);
  }

  int LCA(int u, int v) const {
    while (top[u] != top[v]) {
      if (dep[top[u]] > dep[top[v]]) {
        u = fa[top[u]];
      } else {
        v = fa[top[v]];
      }
    }
    return dep[u] < dep[v] ? u : v;
  }

  void modify(int u, const Tp &d) {
    a[u] = a[u] + d;
    T.modify(dfn[u], d);
    if (dfn[u] + size[u] < n) {
      T.modify(dfn[u] + size[u], -d);
    }
    sta.push_back(u);
  }

  Tp query(int u, int v, int z) const {
    Tp res = T.query(dfn[u] + 1) + T.query(dfn[v] + 1) - T.query(dfn[z] + 1);
    if (fa[z] != -1) {
      res = res - T.query(dfn[fa[z]] + 1);
    }
    return res;
  }

  void clear() {
    while (!sta.empty()) {
      int u = sta.back();
      T.modify(dfn[u], -a[u]);
      if (dfn[u] + size[u] < n) {
        T.modify(dfn[u] + size[u], a[u]);
      }
      a[u] = state();
      sta.pop_back();
    }
  }
};

struct query {
  int u, v, id;
  i64 m;

  query(int u, int v, int id, i64 m = 0) : u(u), v(v), id(id), m(m) {}
};

constexpr int LIM = 1000000000;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  tree<state> T(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    T.add_edge(u, v);
  }
  T.init();
  std::vector<int> a(n);
  i128 sum = 0;
  std::vector<query> Q;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    sum += (i64)a[i] * a[i];
    T.modify(i, a[i]);
    Q.emplace_back(i, a[i], -1);
  }

  int qid = 0;
  std::vector<int> z;
  std::vector<state> all;
  std::vector<i128> ans;
  for (int i = 0; i < q; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int u, v;
      std::cin >> u >> v;
      --u;
      Q.emplace_back(u, a[u], -2);
      Q.emplace_back(u, v, -1);
      T.modify(u, state(v) - state(a[u]));
      sum -= (i64)a[u] * a[u];
      a[u] = v;
      sum += (i64)a[u] * a[u];
    } else {
      int u, v;
      i64 m;
      std::cin >> u >> v >> m;
      --u, --v;
      z.push_back(T.LCA(u, v));
      all.push_back(T.query(u, v, z.back()));
      ans.push_back(sum);
      m = std::max<i64>(0, all.back().s1 - m);
      Q.emplace_back(u, v, qid, m);
      ++qid;
    }
  }
  T.clear();

  std::vector<state> now(qid);

  auto solve = [&](auto &self, int l, int r, const auto &Q) -> void {
    bool ok = false;
    for (auto [u, v, id, m] : Q) {
      ok |= id >= 0;
    }
    if (!ok) {
      return;
    }
    if (l + 1 == r) {
      for (auto [u, v, id, m] : Q) {
        if (id < 0) {
          continue;
        }
        ans[id] -= all[id].s2 - now[id].s2;
        int cnt = all[id].s0 - now[id].s0;
        if (cnt) {
          int d = m - now[id].s1 - i64(l - 1) * (all[id].s0 - now[id].s0);
          ans[id] += (i128)l * l * d;
          ans[id] += (i128)(l - 1) * (l - 1) * (cnt - d);
        }
      }
      return;
    }
    int mid = (l + r) >> 1;
    // std::cerr << "mid = " << mid << ":\n";
    std::vector<query> Q0, Q1;
    for (auto [u, v, id, m] : Q) {
      if (id < 0) {
        if (v < mid) {
          T.modify(u, id == -1 ? state(v) : -state(v));
          Q0.emplace_back(u, v, id);
        } else {
          Q1.emplace_back(u, v, id);
        }
      } else {
        state tmp = now[id] + T.query(u, v, z[id]);
        // std::cerr << " " << tmp.s0 << " " << tmp.s1 << " " << tmp.s2 << "\n";
        bool flag = tmp.s1 + (i64)(mid - 1) * (all[id].s0 - tmp.s0) <= m;
        if (!flag) {
          Q0.emplace_back(u, v, id, m);
        } else {
          now[id] = tmp;
          Q1.emplace_back(u, v, id, m);
        }
      }
    }
    T.clear();
    self(self, l, mid, Q0);
    self(self, mid, r, Q1);
  };

  solve(solve, 1, LIM + 1, Q);
  for (int i = 0; i < qid; ++i) {
    std::cout << ans[i] << "\n";
  }
}
