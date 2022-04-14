#include <bits/stdc++.h>

struct node {
  long long c, s;

  node() : c(), s() {}

  node(int v) : c(1), s(v) {}

  node(long long t_c, long long t_s) : c(t_c), s(t_s) {}

  node operator+(const node &rhs) const {
    return node(c + rhs.c, s + rhs.s);
  }

  node operator-(const node &rhs) const {
    return node(c - rhs.c, s - rhs.s);
  }
};

const int lim = 1000000000;

class seg_tree {
  struct tnode {
    node v;
    tnode *ls, *rs;

    tnode() : v(), ls(), rs() {}
  };

  tnode *rt;

  void insert(tnode *&u, int l, int r, int x) {
    if (u == nullptr) {
      u = new tnode();
    } else {
      u = new tnode(*u);
    }
    u->v = u->v + node(x);
    if (l + 1 == r) {
      return;
    }
    int mid = (l + r) >> 1;
    if (x < mid) {
      insert(u->ls, l, mid, x);
    } else {
      insert(u->rs, mid, r, x);
    }
  }

  std::pair<int, node> find(tnode *u, tnode *v, int l, int r,
                            int L, int R) const {
    tnode tu = u == nullptr ? tnode() : *u;
    tnode tv = v == nullptr ? tnode() : *v;
    if (r <= L || !(tu.v - tv.v).c) {
      return std::make_pair(std::min(r, R), tu.v - tv.v);
    }
    if (l + 1 == r) {
      return std::make_pair(l, node());
    }
    int mid = (l + r) >> 1;
    auto p = find(tu.ls, tv.ls, l, mid, L, R);
    if (p.first == mid) {
      auto q = find(tu.rs, tv.rs, mid, r, L, R);
      q.second = p.second + q.second;
      return q;
    } else {
      return p;
    }
  }

public:
  seg_tree() : rt() {}

  void insert(int x) {
    insert(rt, 0, lim + 1, x);
  }

  seg_tree &operator=(const seg_tree &rhs) {
    rt = rhs.rt;
    return *this;
  }

  std::pair<int, node> find(const seg_tree &rhs,
                            long long L, long long R) const {
    if (L > lim) {
      return std::make_pair(lim + 1, rt == nullptr ? node() : rt->v);
    }
    R = std::min<long long>(R, lim + 1);
    L = std::max<long long>(L, 0);
    return find(rt, rhs.rt, 0, lim + 1, L, R);
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
  std::vector<seg_tree> T(n + 1);
  for (int i = 0; i < n; ++i) {
    T[i + 1] = T[i];
    T[i + 1].insert(a[i]);
  }
  while (q--) {
    int l, r, k;
    std::cin >> l >> r >> k;
    --l;
    auto [p, now] = T[r].find(T[l], 0, lim + 1);
    while (true) {
      if (r - l - now.c == 1) {
        std::cout << 1 << "\n";
        break;
      }
      auto [x, tmp] = T[r].find(T[l], p + std::max(0ll, k - now.s), lim + 1);
      if (x == lim + 1) {
        std::cout << 0 << "\n";
        break;
      }
      while (p <= x) {
        auto [q, tmp] = T[r].find(T[l], x + now.s - k + 1, x + 1);
        if (p == q) {
          break;
        }
        p = q;
        now = tmp;
      }
      if (p <= x) {
        continue;
      }
      while (p <= lim) {
        auto [q, tmp] = T[r].find(T[l], now.s - k + 1, lim + 1);
        if (p == q) {
          break;
        }
        p = q;
        now = tmp;
      }
      if (p <= lim) {
        continue;
      }
      std::cout << r - l - tmp.c << "\n";
      break;
    }
  }
}
