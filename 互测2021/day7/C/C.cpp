#include <bits/stdc++.h>

class set {
public:
  typedef uint32_t size_type;

protected:
  struct node {
    size_type ls, rs;
    size_type v;

    node() : ls(), rs(), v() {}

    node(size_type t_v) : ls(), rs(), v(t_v) {}
  };

  static size_type nd_cnt;
  static node nd[21000001];

  static size_type n;

  size_type rt;

  void up(size_type u) {
    nd[u].v = nd[nd[u].ls].v + nd[nd[u].rs].v;
  }

  void insert(size_type &u, size_type l, size_type r, 
              size_type x, size_type v) {
    nd[nd_cnt] = nd[u];
    u = nd_cnt++;
    if (l + 1 == r) {
      nd[u].v += v;
      return;
    }
    size_type mid = l + ((r - l) >> 1);
    if (x < mid) {
      insert(nd[u].ls, l, mid, x, v);
    } else {
      insert(nd[u].rs, mid, r, x, v);
    }
    up(u);
  }

  static void find(size_type u1, size_type u2, size_type u3, size_type u4,
                   size_type l, size_type r, size_type k,
                   std::vector<size_type> &res) {
    if (res.size() >= k) {
      return;
    }
    size_type v = nd[u1].v + nd[u2].v - nd[u3].v - nd[u4].v;
    if (!v) {
      return;
    }
    if (l + 1 == r) {
      for (size_type i = 0; i < v; ++i) {
        if (res.size() < k) {
          res.push_back(l);
        } else {
          break;
        }
      }
      return;
    }
    size_type mid = l + ((r - l) >> 1);
    find(nd[u1].rs, nd[u2].rs, nd[u3].rs, nd[u4].rs, mid, r, k, res);
    find(nd[u1].ls, nd[u2].ls, nd[u3].ls, nd[u4].ls, l, mid, k, res);
  }

public:
  set() : rt() {}

  static void set_n(size_type t_n) {
    n = t_n;
  }

  void insert(size_type x, size_type v) {
    insert(rt, 0, n, x, v);
  }

  static std::vector<size_type> find(const set &T1, const set &T2,
                                     const set &T3, const set &T4,
                                     size_type k) {
    std::vector<size_type> res;
    res.reserve(k);
    find(T1.rt, T2.rt, T3.rt, T4.rt, 0, n, k, res);
    return res;
  }
};

set::size_type set::nd_cnt = 1;
set::node set::nd[21000001];
set::size_type set::n;

class tree {
  int n;
  std::vector<int> p;
  std::vector<std::vector<int>> E;
  std::vector<int> fa, dep, size, son, top;
  std::vector<set> S;

  void dfs1(int u) {
    S[u].insert(p[u], 1);
    size[u] = 1;
    son[u] = -1;
    for (int v : E[u]) {
      if (v != fa[u]) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        S[v] = S[u];
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

  int LCA(int u, int v) const {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) {
        v = fa[top[v]];
      } else {
        u = fa[top[u]];
      }
    }
    return dep[u] < dep[v] ? u : v;
  }

public:
  tree(int t_n)
  : n(t_n), p(n), E(n),
    fa(n, -1), dep(n), size(n), son(n), top(n),
    S(n + 1) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  void modify(int u, int np) {
    p[u] = np;
  }

  void build() {
    dfs1(0);
    dfs2(0, 0);
    fa[0] = n;
  }

  std::vector<set::size_type> get(int x, int y, int k) {
    int z = LCA(x, y);
    return set::find(S[x], S[y], S[z], S[fa[z]], k);
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

  std::vector<unsigned long long> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  auto v(a);
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < n; ++i) {
    T.modify(i, std::lower_bound(v.begin(), v.end(), a[i]) - v.begin());
  }
  set::set_n(v.size());
  T.build();

  int q;
  std::cin >> q;
  unsigned long long ans = 0;
  std::vector<unsigned long long> val;
  val.reserve(n);
  while (q--) {
    int x, y, m;
    std::cin >> x >> y >> m;
    x = (x ^ ans) % n, y = (y ^ ans) % n;
    auto tmp = T.get(x, y, m * 62);
    for (auto i : tmp) {
      val.push_back(v[i]);
    }
    ans = 0;
    for (int i = 61; i >= 0; --i) {
      int cnt = 0;
      for (auto x : val) {
        cnt += x >> i & 1;
      }
      if (cnt >= m) {
        ans |= 1ull << i;
        auto it = val.begin();
        for (auto x : val) {
          if (x >> i & 1) {
            *it++ = x;
          }
        }
        val.resize(it - val.begin());
      }
    }
    val.clear();
    std::cout << ans << "\n";
  }
}
