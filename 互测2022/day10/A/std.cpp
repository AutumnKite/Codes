#include <bits/stdc++.h>

constexpr int N = 200000;

int pre[N];
long long sum[N + 1];

struct node {
  int p;
  long long s, res, rres;

  node() : p(), s(), res(), rres() {}

  node(int x, int p) : p(p), s(sum[x]), res(sum[x] - sum[p]), rres() {}
};

int get(int x) {
  return x ? pre[x - 1] + 1 : 0;
}

class seg_tree {
  static int enlarge(int n) {
    int res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

  int n, en;
  std::vector<node> val;

  node query_sub(int u, int l, int r, int v) const {
    if (l + 1 == r) {
      return node(l, std::max(get(l), v));
    }
    int mid = (l + r) >> 1;
    if (v < val[u << 1].p) {
      auto res = query_sub(u << 1, l, mid, v);
      res.p = std::max(res.p, val[u << 1 | 1].p);
      res.s = val[u << 1 | 1].s;
      res.res = std::max(res.res, val[u].rres);
      return res;
    } else {
      auto res = query_sub(u << 1 | 1, mid, r, v);
      res.res = std::max(res.res, val[u << 1].s - sum[v]);
      return res;
    }
  }

  node merge(node now, int u, int l, int r) const {
    auto res = query_sub(u, l, r, now.p);
    res.rres = res.res;
    res.res = std::max(res.res, now.res);
    return res;
  }

  void up(int u, int l, int r) {
    val[u] = merge(val[u << 1], u << 1 | 1, (l + r) / 2, r);
  }

  void build(int u, int l, int r) {
    if (l + 1 == r) {
      val[u] = node(l, get(l));
      return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid, r);
    up(u, l, r);
  }

  void update(int u, int l, int r, int x) {
    if (l + 1 == r) {
      val[u] = node(l, get(l));
      return;
    }
    int mid = (l + r) >> 1;
    if (x < mid) {
      update(u << 1, l, mid, x);
    } else {
      update(u << 1 | 1, mid, r, x);
    }
    up(u, l, r);
  }

  void query(int u, int l, int r, int L, int R, node &res) const {
    if (L <= l && r <= R) {
      res = merge(res, u, l, r);
      return;
    }
    int mid = (l + r) >> 1;
    if (L < mid) {
      query(u << 1, l, mid, L, R, res);
    }
    if (mid < R) {
      query(u << 1 | 1, mid, r, L, R, res);
    }
  }

public:
  seg_tree(int n) : n(n), en(enlarge(n) << 1), val(en) {
    build(1, 0, n);
  }

  void update(int x) {
    update(1, 0, n, x);
  }

  long long query(int l, int r) const {
    node res;
    res.p = l;
    query(1, 0, n, l, r, res);
    return res.res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, q;
  std::cin >> n >> m >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    sum[i + 1] = sum[i] + a[i];
  }
  std::vector<int> col(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> col[i];
    --col[i];
  }
  std::vector<std::set<int>> S(m);
  for (int i = 0; i < n; ++i) {
    pre[i] = S[col[i]].empty() ? -1 : *--S[col[i]].end();
    S[col[i]].insert(i);
  }
  seg_tree T(n + 1);
  while (q--) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r;
      std::cin >> l >> r;
      --l;
      std::cout << T.query(l, r + 1) << "\n";
    } else {
      int x, v;
      std::cin >> x >> v;
      --x, --v;
      if (col[x] == v) {
        continue;
      }
      auto it = S[col[x]].upper_bound(x);
      if (it != S[col[x]].end()) {
        pre[*it] = pre[x];
        T.update(*it + 1);
      }
      it = S[v].upper_bound(x);
      if (it != S[v].end()) {
        pre[*it] = x;
        T.update(*it + 1);
      }
      if (it != S[v].begin()) {
        --it;
        pre[x] = *it;
        T.update(x + 1);
      } else {
        pre[x] = -1;
        T.update(x + 1);
      }
      S[col[x]].erase(x);
      S[v].insert(x);
      col[x] = v;
    }
  }
}
/*
3 3 2
1 1 2
1 1 2
2 2 2
1 1 3
*/
