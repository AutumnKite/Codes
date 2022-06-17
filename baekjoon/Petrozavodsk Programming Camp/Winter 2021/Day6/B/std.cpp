#include <bits/stdc++.h>

class seg_tree {
  int n, en, m;
  std::vector<int> min;
  std::vector<long long> sum, sumr;
  
  static int enlarge(int n) {
    int res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

  long long query(int u, int l, int r, int pre) {
    if (l + 1 == r) {
      if (min[u] < pre) {
        return sum[u];
      } else {
        return 0;
      }
    }
    int mid = (l + r) >> 1;
    if (min[u << 1] < pre) {
      return query(u << 1, l, mid, pre) + sumr[u];
    } else {
      return query(u << 1 | 1, mid, r, pre);
    }
  }

  void up(int u, int l, int mid, int r) {
    min[u] = std::min(min[u << 1], min[u << 1 | 1]);
    sumr[u] = query(u << 1 | 1, mid, r, min[u << 1]);
    sum[u] = sum[u << 1] + sumr[u];
  }

  void build(int u, int l, int r, const std::vector<int> &w) {
    if (l + 1 == r) {
      min[u] = m;
      sum[u] = w[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid, w);
    build(u << 1 | 1, mid, r, w);
    up(u, l, mid, r);
  }

  void modify(int u, int l, int r, int x, int v) {
    if (l + 1 == r) {
      min[u] = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (x < mid) {
      modify(u << 1, l, mid, x, v);
    } else {
      modify(u << 1 | 1, mid, r, x, v);
    }
    up(u, l, mid, r);
  }

  long long query(int u, int l, int r, int L, int R, int &pre) {
    if (L <= l && r <= R) {
      long long res = query(u, l, r, pre);
      pre = std::min(pre, min[u]);
      return res;
    }
    int mid = (l + r) >> 1;
    if (R <= mid) {
      return query(u << 1, l, mid, L, R, pre);
    } else if (L >= mid) {
      return query(u << 1 | 1, mid, r, L, R, pre);
    } else {
      long long tmp = query(u << 1, l, mid, L, R, pre);
      return tmp + query(u << 1 | 1, mid, r, L, R, pre);
    }
  }

public:
  seg_tree(std::vector<int> w, int t_m)
      : n(w.size()), en(enlarge(n) << 1), m(t_m), min(en), sum(en), sumr(en) {
    if (n) {
      build(1, 0, n, w);
    }
  }

  void modify(int x, int v) {
    modify(1, 0, n, x, v);
  }

  long long query(int l, int r, int v) {
    if (l >= r) {
      return 0;
    }
    return query(1, 0, n, l, r, v);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  std::vector<std::vector<std::pair<int, int>>> M(n), Q(n);
  std::vector<int> val;
  for (int i = 0; i < q; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, w;
      std::cin >> l >> r >> w;
      val.push_back(w);
      --l;
      M[l].emplace_back(w, i);
      if (r < n) {
        M[r].emplace_back(w, q);
      }
    } else {
      int x, w;
      std::cin >> x >> w;
      --x;
      Q[x].emplace_back(w, i);
    }
  }
  std::sort(val.begin(), val.end());
  int m = val.size();
  seg_tree S(val, q), T(std::vector<int>(val.rbegin(), val.rend()), q);
  std::vector<long long> ans(q, -1);
  for (int i = 0; i < n; ++i) {
    for (auto p : M[i]) {
      p.first = std::lower_bound(val.begin(), val.end(), p.first) - val.begin();
      S.modify(p.first, p.second);
      T.modify(m - 1 - p.first, p.second);
    }
    for (auto p : Q[i]) {
      int x = std::lower_bound(val.begin(), val.end(), p.first) - val.begin();
      int y = std::upper_bound(val.begin(), val.end(), p.first) - val.begin();
      ans[p.second] = S.query(x, m, p.second) +
                      T.query(m - y, m, p.second) -
                      S.query(x, y, p.second);
    }
  }
  for (int i = 0; i < q; ++i) {
    if (ans[i] != -1) {
      std::cout << ans[i] << "\n";
    }
  }
}
