#include <bits/stdc++.h>

constexpr long long INF = std::numeric_limits<long long>::max();

struct line {
  long long k, b;

  line(long long t_k, long long t_b) : k(t_k), b(t_b) {}

  long long get(long long x) const {
    return k * x + b;
  }
};

class seg_tree {
  struct node {
    node *ls, *rs;
    line v;

    node(const line &t_v) : ls(), rs(), v(t_v) {}
  };

  int lim;
  node *rt;

  void insert(node *&u, int l, int r, line v) {
    if (u == nullptr) {
      u = new node(v);
      return;
    }
    if (v.get(l) >= u->v.get(l) && v.get(r) >= u->v.get(r)) {
      return;
    }
    if (v.get(l) <= u->v.get(l) && v.get(r) <= u->v.get(r)) {
      u->v = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (v.get(mid) < u->v.get(mid)) {
      std::swap(v, u->v);
    }
    if (v.get(l) < u->v.get(l)) {
      insert(u->ls, l, mid, v);
    } else {
      insert(u->rs, mid + 1, r, v);
    }
  }

  long long query(node *u, int l, int r, int x) {
    if (u == nullptr) {
      return INF;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
      return std::min(u->v.get(x), query(u->ls, l, mid, x));
    } else {
      return std::min(u->v.get(x), query(u->rs, mid + 1, r, x));
    }
  }

public:
  seg_tree(int t_lim) : lim(t_lim), rt() {}

  void insert(line v) {
    insert(rt, 0, lim, v);
  }

  long long query(int x) {
    return query(rt, 0, lim, x);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> h(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> h[i];
  }
  std::vector<int> w(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> w[i];
  }

  std::vector<long long> sum(n + 1);
  for (int i = 0; i < n; ++i) {
    sum[i + 1] = sum[i] + w[i];
  }
  std::vector<long long> f(n);
  seg_tree T(*std::max_element(h.begin(), h.end()));

  auto insert = [&](int i) {
    T.insert(line(-2 * h[i], f[i] + 1ll * h[i] * h[i] - sum[i + 1]));
  };

  auto query = [&](int i) {
    return T.query(h[i]) + 1ll * h[i] * h[i] + sum[i];
  };

  insert(0);
  for (int i = 1; i < n; ++i) {
    f[i] = query(i);
    insert(i);
  }
  std::cout << f.back() << "\n";
}
