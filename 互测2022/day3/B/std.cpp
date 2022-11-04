#include <bits/stdc++.h>

class fenwick_tree {
  int n;
  std::vector<int> c;
  std::vector<std::pair<int, int>> sta;

public:
  fenwick_tree(int t_n) : n(t_n), c(n + 1) {}

  void modify(int x, int v) {
    sta.emplace_back(x, v);
    for (++x; x <= n; x += x & -x) {
      c[x] += v;
    }
  }

  int query(int x) {
    int s = 0;
    for (; x; x ^= x & -x) {
      s += c[x];
    }
    return s;
  }

  void clear() {
    while (!sta.empty()) {
      for (int x = sta.back().first + 1; x <= n; x += x & -x) {
        c[x] -= sta.back().second;
      }
      sta.pop_back();
    }
  }
};

class tree {
  int n;
  std::vector<std::vector<int>> E;

  std::vector<int> fa, dep, size, son, top;

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
    if (son[u] != -1) {
      dfs2(son[u], tp);
    }
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs2(v, v);
      }
    }
  }

  int LCA(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] > dep[top[v]]) {
        u = fa[top[u]];
      } else {
        v = fa[top[v]];
      }
    }
    return dep[u] < dep[v] ? u : v;
  }

  struct query {
    int d, v, i;

    query(int d, int i) : d(d), v(1), i(i) {}

    query(int d, int v, int i) : d(d), v(v), i(i) {}
  };

  std::vector<int> ans;
  std::vector<std::vector<query>> Q0, Q1, Q2;

  void add(int u, int d, int v, int i) {
    ans[i] += dep[u] * v;
    int lst = -1;
    while (u != -1) {
      Q1[u].emplace_back(d, v, i);
      ans[i] -= v;
      if (lst != -1 && d > 0) {
        Q1[lst].emplace_back(d - 1, -v, i);
      }
      Q2[u].emplace_back(d, v, i);
      lst = top[u];
      u = fa[top[u]];
    }
  }

  std::vector<bool> vis;
  std::vector<int> size0, dep0, cnt;

  void find_root(int u, int fa, int all, int &rt) {
    size0[u] = 1;
    bool ok = true;
    for (int v : E[u]) {
      if (v != fa && !vis[v]) {
        find_root(v, u, all, rt);
        size0[u] += size0[v];
        ok &= size0[v] <= all / 2;
      }
    }
    ok &= all - size0[u] <= all / 2;
    if (ok) {
      rt = u;
    }
  }

  void get_dep(int u, int fa, int &max) {
    while (dep0[u] > max) {
      cnt[++max] = 0;
    }
    ++cnt[dep0[u]];
    size0[u] = 1;
    for (int v : E[u]) {
      if (v != fa && !vis[v]) {
        dep0[v] = dep0[u] + 1;
        get_dep(v, u, max);
        size0[u] += size0[v];
      }
    }
  }

  void query0(int u, int fa, int val, int max) {
    for (auto [d, v, i] : Q0[u]) {
      if (d >= dep0[u]) {
        ans[i] += cnt[std::min(max, d - dep0[u])] * v * val;
      }
    }
    for (int v : E[u]) {
      if (v != fa && !vis[v]) {
        query0(v, u, val, max);
      }
    }
  }

  void solve0(int u, int all) {
    int rt = u;
    find_root(u, -1, all, rt);
    dep0[rt] = 0;
    int max = -1;
    get_dep(rt, -1, max);
    for (int i = 1; i <= max; ++i) {
      cnt[i] += cnt[i - 1];
    }
    query0(rt, -1, 1, max);
    for (int v : E[rt]) {
      if (!vis[v]) {
        max = -1;
        get_dep(v, rt, max);
        for (int i = 1; i <= max; ++i) {
          cnt[i] += cnt[i - 1];
        }
        query0(v, rt, -1, max);
      }
    }
    vis[rt] = true;
    for (int v : E[rt]) {
      if (!vis[v]) {
        solve0(v, size0[v]);
      }
    }
  }

  void dfs3(int u, fenwick_tree &T, int t = 0) {
    T.modify(dep[u] - t, 1);
    for (int v : E[u]) {
      if (v != fa[u]) {
        dfs3(v, T, t);
      }
    }
  }

  void solve1(int u, fenwick_tree &T) {
    T.clear();
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        solve1(v, T);
      }
    }
    if (son[u] != -1) {
      solve1(son[u], T);
    }
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs3(v, T);
      }
    }
    T.modify(dep[u], 1);
    for (auto [d, v, i] : Q1[u]) {
      ans[i] += T.query(std::min(dep[u] + d + 1, n)) * v;
    }
  }

  void solve2(int u, fenwick_tree &T) {
    for (auto [d, v, i] : Q2[u]) {
      ans[i] += T.query(d + 1) * v;
    }
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs3(v, T, dep[u]);
      }
    }
    if (son[u] != -1) {
      solve2(son[u], T);
    }
    T.clear();
    for (int v : E[u]) {
      if (v != fa[u] && v != son[u]) {
        solve2(v, T);
      }
    }
  }

public:
  tree(int t_n) : n(t_n), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  void init() {
    fa.assign(n, -1);
    dep.assign(n, 0);
    size.assign(n, 1);
    son.assign(n, -1);
    top.assign(n, 0);
    dfs1(0);
    dfs2(0, 0);
    ans.clear();
    Q0.assign(n, std::vector<query>());
    Q1.assign(n, std::vector<query>());
    Q2.assign(n, std::vector<query>());
  }

  void add_query(int u, int v, int d) {
    int i = ans.size();
    int z = LCA(u, v);
    ans.push_back(0);
    Q0[z].emplace_back(d, 1, i);
    add(u, d, 1, i);
    add(v, d, 1, i);
    add(z, d, -2, i);
  }

  std::vector<int> solve() {
    vis.assign(n, false);
    size0.assign(n, 0);
    dep0.assign(n, 0);
    cnt.assign(n, 0);
    solve0(0, n);
    fenwick_tree T(n);
    solve1(0, T);
    T.clear();
    solve2(0, T);
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  tree T(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    T.add_edge(u, v);
  }
  T.init();
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int u, v, d;
    std::cin >> u >> v >> d;
    --u, --v;
    T.add_query(u, v, d);
  }
  for (auto x : T.solve()) {
    std::cout << x << "\n";
  }
}
