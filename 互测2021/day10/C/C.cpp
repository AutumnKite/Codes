#include <bits/stdc++.h>

template<typename T>
class set {
  std::priority_queue<T, std::vector<T>, std::greater<T>> Q, R;

public:
  set() : Q(), R() {}

  void insert(const T &x) {
    Q.push(x);
  }

  void erase(const T &x) {
    R.push(x);
  }

  bool empty() const {
    return Q.size() == R.size();
  }

  T top() {
    while (!R.empty() && Q.top() == R.top()) {
      Q.pop();
      R.pop();
    }
    return Q.top();
  }
};

const int INF = std::numeric_limits<int>::max() / 2;

struct node {
  int l, r, min, c;
  unsigned long long sum;
  set<int> S;
};

class segtree {
  constexpr static int enlarge(int n) {
    int res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const int n, en;

  std::vector<node> val;
  std::vector<unsigned long long> tag1, tag2;

  void up(int u) {
    int top = val[u].S.empty() ? INF : val[u].S.top();
    if (val[u].l + 1 == val[u].r) {
      val[u].min = top;
      return;
    }
    int ls = u << 1, rs = u << 1 | 1;
    val[u].sum = val[ls].sum + val[rs].sum;
    val[u].min = std::min(val[ls].min, val[rs].min);
    if (top < val[u].min) {
      val[u].min = top;
      val[u].c = val[u].r - val[u].l;
    } else {
      val[u].c = 0;
      if (val[u].min == val[ls].min) {
        val[u].c += val[ls].c;
      }
      if (val[u].min == val[rs].min) {
        val[u].c += val[rs].c;
      }
    }
  }

  void apply1(int u, unsigned long long v) {
    val[u].sum += (val[u].r - val[u].l) * v;
    tag1[u] += v;
  }

  void apply2(int u, unsigned long long v) {
    val[u].sum += val[u].c * v;
    if (!val[u].S.empty() && val[u].min == val[u].S.top()) {
      tag1[u] += v;
    } else {
      tag2[u] += v;
    }
  }

  void down(int u) {
    int ls = u << 1, rs = u << 1 | 1;
    if (tag1[u]) {
      apply1(ls, tag1[u]);
      apply1(rs, tag1[u]);
      tag1[u] = 0;
    }
    if (tag2[u]) {
      if (val[ls].min == val[u].min) {
        apply2(ls, tag2[u]);
      }
      if (val[rs].min == val[u].min) {
        apply2(rs, tag2[u]);
      }
      tag2[u] = 0;
    }
  }

  void build(int u, int l, int r) {
    val[u].l = l, val[u].r = r;
    if (l + 1 == r) {
      val[u].min = INF;
      val[u].c = 1;
      return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid, r);
    up(u);
  }

  void insert(int u, int l, int r, int L, int R, int x) {
    if (l + 1 < r) {
      down(u);
    }
    if (L <= l && r <= R) {
      val[u].S.insert(x);
      up(u);
      return;
    }
    int mid = (l + r) >> 1;
    if (L < mid) {
      insert(u << 1, l, mid, L, R, x);
    }
    if (mid < R) {
      insert(u << 1 | 1, mid, r, L, R, x);
    }
    up(u);
  }

  void erase(int u, int l, int r, int L, int R, int x) {
    if (l + 1 < r) {
      down(u);
    }
    if (L <= l && r <= R) {
      val[u].S.erase(x);
      up(u);
      return;
    }
    int mid = (l + r) >> 1;
    if (L < mid) {
      erase(u << 1, l, mid, L, R, x);
    }
    if (mid < R) {
      erase(u << 1 | 1, mid, r, L, R, x);
    }
    up(u);
  }

  int query_min(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
      return val[u].min;
    }
    int mid = (l + r) >> 1;
    int res = val[u].S.empty() ? INF : val[u].S.top();
    if (L < mid) {
      res = std::min(res, query_min(u << 1, l, mid, L, R));
    }
    if (mid < R) {
      res = std::min(res, query_min(u << 1 | 1, mid, r, L, R));
    }
    return res;
  }

  void add(int u, int l, int r, int min, int L, int R,
           int need, unsigned long long v) {
    if (L <= l && r <= R) {
      if (std::min(min, val[u].min) == need) {
        if (min == need) {
          apply1(u, v);
        } else {
          apply2(u, v);
        }
      }
      return;
    }
    int mid = (l + r) >> 1;
    if (!val[u].S.empty()) {
      min = std::min(min, val[u].S.top());
    }
    down(u);
    if (L < mid) {
      add(u << 1, l, mid, min, L, R, need, v);
    }
    if (mid < R) {
      add(u << 1 | 1, mid, r, min, L, R, need, v);
    }
    up(u);
  }

  unsigned long long query_sum(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
      return val[u].sum;
    }
    int mid = (l + r) >> 1;
    down(u);
    unsigned long long res = 0;
    if (L < mid) {
      res += query_sum(u << 1, l, mid, L, R);
    }
    if (mid < R) {
      res += query_sum(u << 1 | 1, mid, r, L, R);
    }
    return res;
  }

public:
  segtree(int t_n)
  : n(t_n), en(enlarge(n)), val(en << 1), tag1(en << 1), tag2(en << 1) {
    if (n) {
      build(1, 0, n);
    }
  }

  void insert(int l, int r, int x) {
    if (l < r) {
      insert(1, 0, n, l, r, x);
    }
  }

  void erase(int l, int r, int x) {
    if (l < r) {
      erase(1, 0, n, l, r, x);
    }
  }

  int query_min(int l, int r) {
    if (l < r) {
      return query_min(1, 0, n, l, r);
    } else {
      return INF;
    }
  }

  void add(int l, int r, unsigned long long v) {
    if (l < r) {
      add(1, 0, n, INF, l, r, query_min(l, r), v);
    }
  }

  unsigned long long query_sum(int l, int r) {
    if (l < r) {
      return query_sum(1, 0, n, l, r);
    } else {
      return 0;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  std::vector<std::map<int, int>> mp(q);
  segtree T(n);

  auto erase = [&](int x, int l, int r) {
    auto it = mp[x].lower_bound(l);
    if (it != mp[x].begin()) {
      auto pr = std::prev(it);
      int t = pr->second;
      if (t > l) {
        int nl = pr->first;
        T.erase(nl, t, x);
        if (t > r) {
          pr->second = l;
          mp[x].emplace(r, t);
          T.insert(r, t, x);
          T.insert(nl, l, x);
          return;
        } else {
          pr->second = l;
          T.insert(nl, l, x);
        }
      }
    }
    while (it != mp[x].end() && it->first < r) {
      int t = it->second;
      T.erase(it->first, it->second, x);
      it = mp[x].erase(it);
      if (t > r) {
        mp[x].emplace(r, t);
        T.insert(r, t, x);
        return;
      }
    }
  };

  auto insert = [&](int x, int l, int r) {
    erase(x, l, r);
    mp[x].emplace(l, r);
    T.insert(l, r, x);
  };

  for (int i = 0; i < q; ++i) {
    mp[i].emplace(0, n);
    T.insert(0, n, i);
  }
  for (int k = 0; k < q; ++k) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, x;
      std::cin >> l >> r >> x;
      --l, --x;
      erase(x, l, r);
    } else if (op == 2) {
      int l, r, x;
      std::cin >> l >> r >> x;
      --l, --x;
      insert(x, l, r);
    } else if (op == 3) {
      int l, r;
      unsigned long long v;
      std::cin >> l >> r >> v;
      --l;
      T.add(l, r, v);
    } else {
      int l, r;
      std::cin >> l >> r;
      --l;
      std::cout << T.query_sum(l, r) << "\n";
    }
  }
}
