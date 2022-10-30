#include <bits/stdc++.h>

const long long INF = std::numeric_limits<long long>::max();

int pcnt;
int V[200000];

class convex {
public:
  struct line {
    long long k, b;

    line(long long _k = 0, long long _b = 0) : k(_k), b(_b) {}

    long long get(const int &x) const {
      return k * V[x] + b;
    }
  };

protected:
  const int n;

  struct node {
    line v;
    node *ls, *rs;

    node(line _v) : v(_v), ls(nullptr), rs(nullptr) {}
  };

  node *rt;

  void insert(node *&u, int l, int r, line v) {
    if (u == nullptr) {
      u = new node(v);
      return;
    }
    if (v.get(l) <= u->v.get(l) && v.get(r) <= u->v.get(r)) {
      u->v = v;
      return;
    }
    if (v.get(l) >= u->v.get(l) && v.get(r) >= u->v.get(r)) {
      return;
    }
    int mid = (l + r) >> 1;
    if (v.get(mid) < u->v.get(mid)) {
      std::swap(u->v, v);
    }
    if (v.get(l) < u->v.get(l)) {
      insert(u->ls, l, mid, v);
    } else {
      insert(u->rs, mid + 1, r, v);
    }
  }

  void merge(node *&u, node *&v, int l, int r) {
    if (u == nullptr) {
      std::swap(u, v);
      return;
    }
    if (v == nullptr) {
      return;
    }
    int mid = (l + r) >> 1;
    merge(u->ls, v->ls, l, mid);
    merge(u->rs, v->rs, mid + 1, r);
    insert(u, l, r, v->v);
    delete v;
    v = nullptr;
  }

  long long query(node *u, int l, int r, int x) {
    if (u == nullptr) {
      return INF;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
      return std::min(query(u->ls, l, mid, x), u->v.get(x));
    } else {
      return std::min(query(u->rs, mid + 1, r, x), u->v.get(x));
    }
  }

  void clear(node *u) {
    if (u == nullptr) {
      return;
    }
    clear(u->ls);
    clear(u->rs);
    delete u;
  }

public:
  convex(int _n) : n(_n), rt(nullptr) {}

  void insert(const line &v) {
    insert(rt, 0, n - 1, v);
  }

  void merge(convex &c) {
    merge(rt, c.rt, 0, n - 1);
  }

  long long query(int x) {
    return query(rt, 0, n - 1, x);
  }

  void clear() {
    clear(rt);
    rt = nullptr;
  }

  convex &operator=(const convex &rhs) {
    clear();
    rt = rhs.rt;
    return *this;
  }
};

class segment_tree {
protected:
  static int enlarge(int n) {
    int res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

  int n, en, idx;
  std::vector<convex> a;
  std::vector<std::vector<std::pair<int, int>>> Q;
  std::vector<convex> T;

  void insert(int u, int l, int r, int x, const convex::line &v) {
    T[u].insert(v);
    if (l + 1 == r) {
      return;
    }
    int mid = (l + r + 1) >> 1;
    if (x < mid) {
      insert(u << 1, l, mid, x, v);
    } else {
      insert(u << 1 | 1, mid, r, x, v);
    }
  }

  void add_query(int u, int l, int r, int L, int R, int x, int id) {
    if (L <= l && r <= R) {
      Q[u].emplace_back(x, id);
      return;
    }
    int mid = (l + r + 1) >> 1;
    if (L < mid) {
      add_query(u << 1, l, mid, L, R, x, id);
    }
    if (R > mid) {
      add_query(u << 1 | 1, mid, r, L, R, x, id);
    }
  }

  std::vector<long long> ans;

  void get_ans(int u, int l, int r) {
    if (l + 1 == r) {
      T[u].merge(a[l]);
    } else {
      int mid = (l + r + 1) >> 1;
      get_ans(u << 1, l, mid);
      get_ans(u << 1 | 1, mid, r);
      T[u].merge(T[u << 1]);
      T[u].merge(T[u << 1 | 1]);
    }
    for (auto [x, id] : Q[u]) {
      ans[id] = std::min(ans[id], T[u].query(x));
    }
  }

public:
  segment_tree(int _n, int _m)
  : n(_n), en(enlarge(n) << 1), idx(0), a(n, convex(_m)), 
    Q(en), T(en, convex(_m)) {}

  void insert(int x, const convex::line &v) {
    a[x].insert(v);
  }

  void add_query(int l, int r, int x) {
    add_query(1, 0, n, l, r, x, idx++);
  }

  std::vector<long long> get_ans() {
    ans.assign(idx, INF);
    get_ans(1, 0, n);
    T[1].clear();
    return ans;
  }
};

class tree {
public:
  struct query {
    int u, x, id;

    query(int _u, int _x, int _id) : u(_u), x(_x), id(_id) {}
  };

  std::vector<query> Q;

protected:
  int n, rt, dfn_idx;
  std::vector<int> a;
  std::vector<std::vector<std::pair<int, long long>>> E;

  std::vector<int> fa, dep, sz, son, top, dfn;
  std::vector<long long> dis;

  std::vector<std::vector<int>> lt;

  int idx;
  std::vector<std::vector<int>> Q1, Q2, Q3, Q4;
  std::vector<int> c1, c2, c3, c4;

  void dfs1(int u) {
    sz[u] = 1;
    son[u] = -1;
    for (auto [v, w] : E[u]) {
      if (v != fa[u]) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dis[v] = dis[u] + w;
        dfs1(v);
        sz[u] += sz[v];
        if (son[u] == -1 || sz[v] > sz[son[u]]) {
          son[u] = v;
        }
      }
    }
  }

  void dfs2(int u, int tp) {
    dfn[u] = dfn_idx++;
    top[u] = tp;
    if (son[u] != -1) {
      dfs2(son[u], tp);
    }
    for (auto [v, w] : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs2(v, v);
      }
    }
  }

  std::vector<long long> sum;
  std::vector<long long> ans;

  void upd(int id, long long s) {
    ans[id] = std::min(ans[id], s);
  }

  std::vector<convex> con;

  void dfs3(int u, convex &now1, convex &now2) {
    for (int v : lt[u]) {
      now1.insert(convex::line(a[v], 2 * dis[v] - 2 * dis[u]));
      now2.insert(convex::line(a[v], 2 * dis[v] - 4 * dis[u]));
    }
    for (auto i : Q1[u]) {
      upd(Q[i].id, now1.query(Q[i].x));
    }
    for (auto i : Q3[u]) {
      upd(Q[i].id, now2.query(Q[i].x) + 2 * dis[Q[i].u]);
    }
    if (son[u] != -1) {
      dfs3(son[u], now1, now2);
    }
    now1.clear(), now2.clear();
    for (auto [v, w] : E[u]) {
      if (v != fa[u] && v != son[u]) {
        dfs3(v, now1, now2);
        now1.clear(), now2.clear();
      }
    }
    con[u].insert(convex::line(a[u], 2 * dis[u]));
    for (auto [v, w] : E[u]) {
      if (v != fa[u]) {
        con[u].merge(con[v]);
      }
    }
    for (auto i : Q3[u]) {
      upd(Q[i].id, con[u].query(Q[i].x) - 4 * dis[u] + 2 * dis[Q[i].u]);
    }
    for (auto i : Q1[u]) {
      upd(Q[i].id, con[u].query(Q[i].x) - 2 * dis[u]);
    }
    for (auto i : Q4[u]) {
      upd(Q[i].id, con[u].query(Q[i].x) - 2 * dis[u]);
    }
  }

public:
  tree(std::vector<int> _a, int _rt)
  : n(_a.size()), rt(_rt), dfn_idx(0), a(_a), E(n),
    fa(n), dep(n), sz(n), son(n), top(n), dfn(n), dis(n), lt(n),
    idx(0), Q1(n), Q2(n), Q3(n), Q4(n), c1(n), c2(n), c3(n), c4(n) {}

  void add_edge(int u, int v, long long w) {
    E[u].emplace_back(v, w);
    E[v].emplace_back(u, w);
  }

  void build() {
    fa[rt] = -1;
    dep[rt] = 0;
    dis[rt] = 0;
    dfs1(rt);
    dfs2(rt, rt);
    for (int u = 0; u < n; ++u) {
      lt[u].reserve(sz[u] - (son[u] == -1 ? 0 : sz[son[u]]));
    }
    for (int u = 0; u < n; ++u) {
      for (int v = u; v != -1; v = fa[top[v]]) {
        lt[v].push_back(u);
      }
    }
  }

  int LCA(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) {
        std::swap(u, v);
      }
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }

  void add_query(int u, int v, int x) {
    V[pcnt++] = x;
    int z = LCA(u, v);
    sum.emplace_back(dis[u] + dis[v] - 2 * dis[z]);
    Q.emplace_back(u, x, idx);
    Q.emplace_back(v, x, idx);
    Q.emplace_back(z, x, idx);
    for (int p = u; p != -1; p = fa[top[p]]) {
      if (top[p] == top[z]) {
        ++c2[p];
        ++c4[p];
        break;
      }
      ++c1[p];
    }
    for (int p = v; p != -1; p = fa[top[p]]) {
      if (top[p] == top[z]) {
        ++c2[p];
        ++c4[p];
        break;
      }
      ++c1[p];
    }
    for (int p = z; p != -1; p = fa[top[p]]) {
      ++c3[p];
    }
    ++idx;
  }

  std::vector<long long> get_ans() {
    std::sort(V, V + pcnt);
    pcnt = std::unique(V, V + pcnt) - V;

    ans.assign(idx, INF);
    segment_tree T(n, pcnt);
    for (int u = 0; u < n; ++u) {
      for (int v : lt[u]) {
        T.insert(dfn[u], convex::line(a[v], 2 * dis[v] - 2 * dis[u]));
      }
    }
    for (int i = 0; i < n; ++i) {
      Q1[i].reserve(c1[i]);
      Q2[i].reserve(c2[i]);
      Q3[i].reserve(c3[i]);
      Q4[i].reserve(c4[i]);
    }
    for (int i = 0; i < (int)Q.size(); i += 3) {
      int tmp = std::lower_bound(V, V + pcnt, Q[i].x) - V;
      Q[i].x = Q[i + 1].x = Q[i + 2].x = tmp;
      int u = Q[i].u, v = Q[i + 1].u, z = Q[i + 2].u;
      for (int p = u; p != -1; p = fa[top[p]]) {
        if (top[p] == top[z]) {
          Q2[p].emplace_back(i + 2);
          Q4[p].emplace_back(i);
          break;
        }
        Q1[p].emplace_back(i);
      }
      for (int p = v; p != -1; p = fa[top[p]]) {
        if (top[p] == top[z]) {
          Q2[p].emplace_back(i + 2);
          Q4[p].emplace_back(i + 1);
          break;
        }
        Q1[p].emplace_back(i + 1);
      }
      for (int p = z; p != -1; p = fa[top[p]]) {
        Q3[p].emplace_back(i + 2);
      }
    }
    for (int u = 0; u < n; ++u) {
      for (auto i : Q2[u]) {
        T.add_query(dfn[Q[i].u], dfn[u] + 1, Q[i].x);
      }
    }
    auto tans = T.get_ans();
    auto it = tans.begin();
    for (int u = 0; u < n; ++u) {
      for (auto i : Q2[u]) {
        upd(Q[i].id, *it);
        ++it;
      }
    }
    con.assign(n, convex(pcnt));
    convex tmp1(pcnt), tmp2(pcnt);
    dfs3(rt, tmp1, tmp2);
    con[0].clear();
    for (int i = 0; i < idx; ++i) {
      ans[i] += sum[i];
    }
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m, q;
  std::cin >> n >> m >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  tree T(a, 0);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    long long w;
    std::cin >> u >> v >> w;
    --u, --v;
    T.add_edge(u, v, w);
  }
  T.build();
  for (int i = 0; i < q; ++i) {
    long long x, y;
    std::cin >> x >> y;
    --x, --y;
    T.add_query(x % n, y % n, abs(x / n - y / n));
  }
  auto ans = T.get_ans();
  for (int i = 0; i < q; ++i) {
    std::cout << ans[i] << "\n";
  }
}
