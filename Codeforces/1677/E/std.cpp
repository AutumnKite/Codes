#include <bits/stdc++.h>

class seg_tree {
  int n, en;
  std::vector<int> val, tag;

  constexpr static int enlarge(int n) {
    int res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

  void up(int u, int l, int r) {
    if (tag[u]) {
      val[u] = r - l;
    } else {
      val[u] = val[u << 1] + val[u << 1 | 1];
    }
  }

  void modify(int u, int l, int r, int L, int R, int d) {
    if (L <= l && r <= R) {
      tag[u] += d;
      up(u, l, r);
      return;
    }
    int mid = (l + r) >> 1;
    if (L < mid) {
      modify(u << 1, l, mid, L, R, d);
    }
    if (R > mid) {
      modify(u << 1 | 1, mid, r, L, R, d);
    }
    up(u, l, r);
  }

  int query(int u, int l, int r, int L, int R) const {
    if (L <= l && r <= R) {
      return val[u];
    }
    if (tag[u]) {
      return std::min(R, r) - std::max(L, l);
    }
    int mid = (l + r) >> 1;
    if (R <= mid) {
      return query(u << 1, l, mid, L, R);
    } else if (L >= mid) {
      return query(u << 1 | 1, mid, r, L, R);
    } else {
      return query(u << 1, l, mid, L, R) + query(u << 1 | 1, mid, r, L, R);
    }
  }

public:
  seg_tree(int t_n) : n(t_n), en(enlarge(n)), val(en << 1), tag(en << 1) {}

  void modify(int l, int r, int d) {
    modify(1, 0, n, l, r, d);
  }

  int query(int l, int r) const {
    return query(l, r);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
}
