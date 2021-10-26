#pragma GCC optimize(3)

#include <bits/stdc++.h>

template<typename Val, 
         typename VV = std::plus<>>
class seg_tree {
public:
  typedef std::size_t size_type;

private:
  constexpr static size_type enlarge(size_type n) {
    size_type res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const size_type n, en;

  VV fun_vv;

  std::vector<Val> val;

  void up(size_type u) {
    val[u] = fun_vv(val[u << 1], val[u << 1 | 1]);
  }

  template<typename T>
  void build(size_type u, size_type l, size_type r, 
             const std::vector<T> &a) {
    if (l + 1 == r) {
      val[u] = Val(a[l]);
      return;
    }
    size_type mid = (l + r) >> 1;
    build(u << 1, l, mid, a);
    build(u << 1 | 1, mid, r, a);
    up(u);
  }

  void modify(size_type u, size_type l, size_type r, 
              size_type x, const Val &v) {
    if (l + 1 == r) {
      val[u] = v;
      return;
    }
    size_type mid = (l + r) >> 1;
    if (x < mid) {
      modify(u << 1, l, mid, x, v);
    } else {
      modify(u << 1 | 1, mid, r, x, v);
    }
    up(u);
  }

  Val query(size_type u, size_type l, size_type r, 
            size_type L, size_type R) const {
    if (L <= l && r <= R) {
      return val[u];
    }
    size_type mid = (l + r) >> 1;
    if (R <= mid) {
      return query(u << 1, l, mid, L, R);
    } else if (L >= mid) {
      return query(u << 1 | 1, mid, r, L, R);
    } else {
      return fun_vv(query(u << 1, l, mid, L, R), 
                    query(u << 1 | 1, mid, r, L, R));
    }
  }

public:
  seg_tree() : seg_tree(0) {}

  seg_tree(size_type _n)
  : n(_n), en(enlarge(n)), val(en << 1) {}

  template<typename T>
  seg_tree(const std::vector<T> &a)
  : n(a.size()), en(enlarge(n)), val(en << 1) {
    if (n) {
      build(1, 0, n, a);
    }
  }

  size_type size() const {
    return n;
  }

  void modify(size_type x, const Val &v) {
    modify(1, 0, n, x, v);
  }

  Val query(size_type l, size_type r) const {
    if (l < r) {
      return query(1, 0, n, l, r);
    } else {
      return Val();
    }
  }
};

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

int len, V[100002];

struct state {
  long long v0, v1, v;

  state() : v0(INF), v1(INF), v(INF) {}

  state(long long _v0, long long _v1, long long _v)
  : v0(_v0), v1(_v1), v(_v) {}

  state operator+(const state &rhs) const {
    return state(std::min(v0, rhs.v0), std::min(v1, rhs.v1), std::min(v, rhs.v));
  }

  void operator+=(long long d) {
    v0 += d;
    v1 += d;
    v += d;
  }
};

class special_seg_tree {
protected:
  struct node {
    node *ls, *rs;
    state v;
    long long t;

    node() : ls(nullptr), rs(nullptr), v(), t() {}
  };

  node *rt;

  void up(node *u) {
    if (u->ls == nullptr) {
      u->v = u->rs->v;
    } else if (u->rs == nullptr) {
      u->v = u->ls->v;
    } else {
      u->v = u->ls->v + u->rs->v;
    }
  }

  void apply(node *u, long long v) {
    if (u == nullptr) {
      return;
    }
    u->v += v;
    u->t += v;
  }

  void down(node *u) {
    if (u != nullptr && u->t) {
      apply(u->ls, u->t);
      apply(u->rs, u->t);
      u->t = 0;
    }
  }

  void insert(node *&u, int l, int r, int x, long long v) {
    if (u == nullptr) {
      u = new node();
    }
    if (l + 1 == r) {
      u->v = u->v + state(v - V[l], v + V[l], v);
      return;
    }
    int mid = l + ((r - l) >> 1);
    down(u);
    if (x < mid) {
      insert(u->ls, l, mid, x, v);
    } else {
      insert(u->rs, mid, r, x, v);
    }
    up(u);
  }

  void modify(node *&u, int l, int r, int L, int R, long long v) {
    if (u == nullptr) {
      return;
    }
    if (L <= l && r <= R) {
      apply(u, v);
      return;
    }
    int mid = l + ((r - l) >> 1);
    down(u);
    if (L < mid) {
      modify(u->ls, l, mid, L, R, v);
    }
    if (R > mid) {
      modify(u->rs, mid, r, L, R, v);
    }
    up(u);
  }

  state query(node *u, int l, int r, int L, int R) {
    if (u == nullptr) {
      return state();
    }
    if (L <= l && r <= R) {
      return u->v;
    }
    int mid = l + ((r - l) >> 1);
    down(u);
    if (R <= mid) {
      return query(u->ls, l, mid, L, R);
    } else if (L >= mid) {
      return query(u->rs, mid, r, L, R);
    } else {
      return query(u->ls, l, mid, L, R)
           + query(u->rs, mid, r, L, R);
    }
  }

  void merge(node *&u, node *&v, int l, int r) {
    if (v == nullptr) {
      return;
    }
    if (u == nullptr) {
      std::swap(u, v);
      return;
    }
    if (l + 1 == r) {
      u->v = u->v + v->v;
      delete v;
      v = nullptr;
      return;
    }
    int mid = l + ((r - l) >> 1);
    down(u);
    down(v);
    merge(u->ls, v->ls, l, mid);
    merge(u->rs, v->rs, mid, r);
    delete v;
    v = nullptr;
    up(u);
  }

public:
  special_seg_tree() : rt(nullptr) {}

  void insert(int x, long long v) {
    insert(rt, 0, len, x, v);
  }

  void modify(int l, int r, long long v) {
    if (l < r) {
      modify(rt, 0, len, l, r, v);
    }
  }

  state query(int l, int r) {
    if (l < r) {
      return query(rt, 0, len, l, r);
    } else {
      return state();
    }
  }

  void merge(special_seg_tree &T) {
    merge(rt, T.rt, 0, len);
  }
};

template<typename T>
struct min {
  const T &operator()(const T &a, const T &b) const {
    return std::min(a, b);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, L;
  std::cin >> n >> L;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  a.insert(a.begin(), 0);
  ++n;

  for (int i = 0; i < n; ++i) {
    V[len++] = a[i];
    V[len++] = a[i] - L;
  }
  std::sort(V, V + len);
  len = std::unique(V, V + len) - V;

  std::vector<int> R(len);
  for (int i = 0; i < len; ++i) {
    R[i] = std::upper_bound(V, V + len, V[i] + L) - V;
  }

  std::vector<int> p0(n), p1(n);
  for (int i = 0; i < n; ++i) {
    p0[i] = std::lower_bound(V, V + len, a[i]) - V;
    p1[i] = std::lower_bound(V, V + len, a[i] - L) - V;
  }

  std::vector<int> nxt(n);
  std::vector<int> pos(len, n);
  for (int i = n - 1; i >= 0; --i) {
    nxt[i] = pos[p0[i]];
    pos[p0[i]] = i;
  }

  seg_tree<int, min<int>> T(pos);

  auto find = [&](int i, int x, int y) {
    if (x > y) {
      std::swap(x, y);
    }
    int p = i;
    while (p < n && ((x <= p0[p] && p0[p] < R[x]) 
                  || (y <= p0[p] && p0[p] < R[y]))) {
      ++p;
    }
    return p;
    // return std::min({0 < x ? T.query(0, x) : n,
    //                  R[x] < y ? T.query(R[x], y) : n,
    //                  R[y] < len ? T.query(R[y], len) : n});
  };

  long long ans = INF;
  std::vector<special_seg_tree> f(n), g(n);
  f[0].insert(p0[0], 0);

  for (int i = 0; i < n; ++i) {
    do {
      int t = p0[i];
      int k = find(i, t, t);
      if (k >= n) {
        ans = std::min(ans, f[i].query(0, len).v);
      } else {
        int t0 = p1[k];
        int t1 = p0[k];
        for (int j = t0; j <= t1; ++j) {
          long long v = f[i].query(j, j + 1).v;
          if (v == INF) {
            continue;
          }
          int p = find(i, t, j);
          if (p >= n) {
            ans = std::min(ans, v);
          } else {
            if (a[p] > a[i]) {
              g[p].insert(j, v + a[p] - a[i] - L);
            } else {
              f[p].insert(j, v + a[i] - a[p]);
            }
            if (a[p] > V[j]) {
              g[p].insert(t, v + a[p] - V[j] - L);
            } else {
              f[p].insert(t, v + V[j] - a[p]);
            }
          }
        }
        long long v0 = f[i].query(0, t0 + 1).v0;
        if (v0 != INF) {
          g[k].insert(t, v0 + a[k] - L);
        }
        long long v1 = f[i].query(t1, len).v1;
        if (v1 != INF) {
          f[k].insert(t, v1 - a[k]);
        }
        if (a[k] > a[i]) {
          f[i].modify(0, len, a[k] - a[i] - L);
          g[k].merge(f[i]);
        } else {
          f[i].modify(0, len, a[i] - a[k]);
          f[k].merge(f[i]);
        }
      }
    } while (0);
    do {
      int t = p1[i];
      int k = find(i, t, t);
      if (k >= n) {
        ans = std::min(ans, g[i].query(0, len).v);
      } else {
        int t0 = p1[k];
        int t1 = p0[k];
        for (int j = t0; j <= t1; ++j) {
          long long v = g[i].query(j, j + 1).v;
          if (v == INF) {
            continue;
          }
          int p = find(i, t, j);
          if (p >= n) {
            ans = std::min(ans, v);
          } else {
            if (a[p] > a[i]) {
              g[p].insert(j, v + a[p] - a[i]);
            } else {
              f[p].insert(j, v + a[i] - a[p] - L);
            }
            if (a[p] > V[j]) {
              g[p].insert(t, v + a[p] - V[j] - L);
            } else {
              f[p].insert(t, v + V[j] - a[p]);
            }
          }
        }
        long long v0 = g[i].query(0, t0 + 1).v0;
        if (v0 != INF) {
          g[k].insert(t, v0 + a[k] - L);
        }
        long long v1 = g[i].query(t1, len).v1;
        if (v1 != INF) {
          f[k].insert(t, v1 - a[k]);
        }
        if (a[k] > a[i]) {
          g[i].modify(0, len, a[k] - a[i]);
          g[k].merge(g[i]);
        } else {
          g[i].modify(0, len, a[i] - a[k] - L);
          f[k].merge(g[i]);
        }
      }
    } while (0);
    T.modify(p0[i], nxt[i]);
  }
  std::cout << ans << "\n";
}
