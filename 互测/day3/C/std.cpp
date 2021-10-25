#include <bits/stdc++.h>

template<typename Val, 
         typename VV = std::plus<>>
class dynamic_seg_tree {
public:
  typedef std::size_t size_type;

  const Val E;

protected:
  const size_type n;

  VV fun_vv;

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
    } else {
      u = new node(*u);
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
  dynamic_seg_tree(size_type _n)
  : E(), n(_n), rt(nullptr) {}

  dynamic_seg_tree(size_type _n, const Val &_E)
  : E(_E), n(_n), rt(nullptr) {}

  void modify(size_type x, const Val &v) {
    modify(rt, 0, n, x, v);
  }

  Val query(size_type l, size_type r) const {
    if (l < r) {
      return query(rt, 0, n, l, r);
    } else {
      return E;
    }
  }

  dynamic_seg_tree &operator=(const dynamic_seg_tree &T) {
    rt = T.rt;
    return *this;
  }
};

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

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

  std::vector<dynamic_seg_tree<int, min<int>>> T(n + 1, 
    dynamic_seg_tree<int, min<int>>(1e9 + 1, n));
  for (int i = n - 1; i >= 0; --i) {
    T[i] = T[i + 1];
    T[i].modify(a[i], i);
  }

  auto find = [&](int i, int x, int y) {
    if (x > y) {
      std::swap(x, y);
    }
    return std::min({T[i].query(0, std::max(0, x)),
                     T[i].query(x + L + 1, std::max(0, y)),
                     T[i].query(y + L + 1, 1e9 + 1)});
  };

  auto upd = [&](std::map<int, long long> &mp, int x, long long v) {
    auto it = mp.find(x);
    if (it == mp.end()) {
      mp.emplace(x, v);
    } else {
      it->second = std::min(it->second, v);
    }
  };

  long long ans = INF;
  std::vector<std::map<int, long long>> f(n), g(n);
  std::vector<long long> df(n), dg(n);
  std::vector<std::map<int, long long>> af(n), ag(n);
  std::vector<bool> uf(n), ug(n);
  f[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (auto [x, v] : af[i]) {
      upd(f[i], x, v - df[i]);
    }
    for (auto [x, v] : ag[i]) {
      upd(g[i], x, v - dg[i]);
    }
    std::cerr << "f " << i << ":\n";
    for (auto [x, v] : f[i]) {
      std::cerr << x << " " << v + df[i] << "\n";
    }
    std::cerr << "g " << i << ":\n";
    for (auto [x, v] : g[i]) {
      std::cerr << x << " " << v + dg[i] << "\n";
    }
    std::cerr << "\n";
    bool ok = false;
    do {
      int k = find(i, a[i], a[i]);
      if (k == n) {
        ok = true;
        for (auto [x, v] : f[i]) {
          ans = std::min(ans, v + df[i]);
        }
      } else {
        for (int j = a[k] - L; j <= a[k]; ++j) {
          auto it = f[i].find(j);
          if (it == f[i].end()) {
            continue;
          }
          int p = find(i, a[i], j);
          if (p == n) {
            ans = std::min(ans, it->second + df[i]);
          } else {
            if (a[p] > a[i]) {
              upd(ag[p], j, it->second + df[i] + a[p] - a[i] - L);
            } else {
              upd(af[p], j, it->second + df[i] + a[i] - a[p]);
            }
            if (a[p] > j) {
              upd(ag[p], a[i], it->second + df[i] + a[p] - j - L);
            } else {
              upd(af[p], a[i], it->second + df[i] + j - a[p]);
            }
          }
        }
        if (a[k] > a[i]) {
          if (!ug[k]) {
            ug[k] = true;
            g[k].swap(f[i]);
            dg[k] = df[i] + a[k] - a[i] - L;
          }
        } else {
          if (!uf[k]) {
            uf[k] = true;
            f[k].swap(f[i]);
            df[k] = df[i] + a[i] - a[k];
          }
        }
      }
    } while (0);
    do {
      int k = find(i, a[i] - L, a[i] - L);
      if (k == n) {
        ok = true;
        for (auto [x, v] : g[i]) {
          ans = std::min(ans, v + dg[i]);
        }
      } else {
        for (int j = a[k] - L; j <= a[k]; ++j) {
          auto it = g[i].find(j);
          if (it == g[i].end()) {
            continue;
          }
          int p = find(i, a[i] - L, j);
          if (p == n) {
            ans = std::min(ans, it->second + dg[i]);
          } else {
            if (a[p] > a[i]) {
              upd(ag[p], j, it->second + dg[i] + a[p] - a[i]);
            } else {
              upd(af[p], j, it->second + dg[i] + a[i] - a[p] - L);
            }
            if (a[p] > j) {
              upd(ag[p], a[i] - L, it->second + dg[i] + a[p] - j - L);
            } else {
              upd(af[p], a[i] - L, it->second + dg[i] + j - a[p]);
            }
          }
        }
        if (a[k] > a[i]) {
          if (!ug[k]) {
            ug[k] = true;
            g[k].swap(g[i]);
            dg[k] = dg[i] + a[k] - a[i];
          }
        } else {
          if (!uf[k]) {
            uf[k] = true;
            f[k].swap(g[i]);
            df[k] = dg[i] + a[i] - a[k] - L;
          }
        }
      }
    } while (0);
    if (ok) {
      std::cout << ans << "\n";
      return 0;
    }
  }
}
