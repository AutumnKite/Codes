#include <bits/stdc++.h>

class dynamic_seg_tree {
public:
  static int n;

protected:
  struct node {
    node *ls, *rs;
    int v;

    node(int t_v) : ls(), rs(), v(t_v) {}
  };

  node *rt;
  
  void up(node *u) {
    u->v = (u->ls == nullptr ? 0 : u->ls->v) +
           (u->rs == nullptr ? 0 : u->rs->v);
  }

  void add(node *&u, int l, int r, int x, int v) {
    if (u == nullptr) {
      u = new node(0);
    } else {
      u = new node(*u);
    }
    if (l + 1 == r) {
      u->v += v;
      return;
    }
    int mid = l + ((r - l) >> 1);
    if (x < mid) {
      add(u->ls, l, mid, x, v);
    } else {
      add(u->rs, mid, r, x, v);
    }
    up(u);
  }

  int query(node *u, int l, int r, int L, int R) const {
    if (u == nullptr) {
      return 0;
    }
    if (L <= l && r <= R) {
      return u->v;
    }
    int mid = l + ((r - l) >> 1);
    if (R <= mid) {
      return query(u->ls, l, mid, L, R);
    } else if (L >= mid) {
      return query(u->rs, mid, r, L, R);
    } else {
      return query(u->ls, l, mid, L, R) + query(u->rs, mid, r, L, R);
    }
  }

public:
  dynamic_seg_tree() : rt() {}

  void add(int x, int v) {
    add(rt, 0, n, x, v);
  }

  int query(int l, int r) const {
    if (l < r) {
      return query(rt, 0, n, l, r);
    } else {
      return 0;
    }
  }
};

int dynamic_seg_tree::n;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> g(n), c(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> g[i] >> c[i];
    c[i] = (m - c[i]) % m;
  }
  std::vector<int> d(n - 1), x(n);
  for (int i = 0; i < n - 1; ++i) {
    std::cin >> d[i];
    x[i + 1] = (x[i] + d[i]) % m;
  }
  for (int i = 0; i < n; ++i) {
    c[i] = (c[i] - x[i]) % m;
  }

  dynamic_seg_tree::n = m;
  std::vector<dynamic_seg_tree> T(n + 1);
  for (int i = 0; i < n; ++i) {
    T[i + 1] = T[i];
    if (c[i] + g[i] >= m) {
      T[i + 1].add(c[i], 1);
      T[i + 1].add(0, 1);
      T[i + 1].add(c[i] + g[i] - m, -1);
    } else {
      T[i + 1].add(c[i], 1);
      T[i + 1].add(c[i] + g[i], -1);
    }
  }

  std::vector<int> nxt(n);
  for (int i = 0; i < n; ++i) {
    int v = T[i].query(0, c[i] + 1);
    int l = i, r = n + 1;
    while (l + 1 < r) {
      int mid = (l + r) >> 1;
      if (T[mid].query(0, c[i] + 1) - v >= mid - i) {
        l = mid;
      } else {
        r = mid;
      }
    }
    nxt[i] = l;
  }
  std::vector<long long> f(n);
  for (int i = n - 1; i >= 0; --i) {
    if (nxt[i] < n) {
      f[i] = f[nxt[i]] + (c[nxt[i]] - c[i] + m) % m;
    }
  }
  long long ans = f[0];
  for (int i = 0; i < n; ++i) {
    int l = 0, r = n + 1;
    while (l + 1 < r) {
      int mid = (l + r) >> 1;
      if (T[mid].query(0, c[i] + 1) >= mid) {
        l = mid;
      } else {
        r = mid;
      }
    }
    ans = std::min(ans, f[l] + (c[l] - c[i] + m) % m);
  }
  std::cout << ans + std::accumulate(d.begin(), d.end(), 0ll) << "\n";
}
