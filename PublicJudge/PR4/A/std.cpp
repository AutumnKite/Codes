#include <bits/stdc++.h>

constexpr int LIM = 1000000000;

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

struct line {
  long long k, b;

  line(long long t_k, long long t_b) : k(t_k), b(t_b) {}

  long long get(int x) const {
    return k * x + b;
  }
};

class lichao_tree {
  struct node {
    node *ls, *rs;
    line v;

    node(const line &t_v) : ls(), rs(), v(t_v) {}
  };

  node *rt;

  void insert(node *&u, int l, int r, line v) {
    if (u == nullptr) {
      u = new node(v);
      return;
    }
    if (v.get(l) <= u->v.get(l) && v.get(r) <= u->v.get(r)) {
      return;
    }
    if (v.get(l) >= u->v.get(l) && v.get(r) >= u->v.get(r)) {
      u->v = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (v.get(mid) >= u->v.get(mid)) {
      std::swap(v, u->v);
    }
    if (v.get(l) >= u->v.get(l)) {
      insert(u->ls, l, mid, v);
    } else {
      insert(u->rs, mid + 1, r, v);
    }
  }

  long long query(node *u, int l, int r, int x) const {
    if (u == nullptr) {
      return -INF;
    }
    if (l == r) {
      return u->v.get(x);
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
      return std::max(u->v.get(x), query(u->ls, l, mid, x));
    } else {
      return std::max(u->v.get(x), query(u->rs, mid + 1, r, x));
    }
  }

public:
  lichao_tree() : rt() {}

  void insert(line v) {
    insert(rt, 1, LIM, v);
  }

  long long query(int x) const {
    return query(rt, 1, LIM, x);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n), w(n);
  std::vector<int> val;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i] >> b[i] >> w[i];
    val.push_back(a[i]);
    val.push_back(b[i]);
  }
  val.push_back(1);
  std::sort(val.begin(), val.end());
  val.erase(std::unique(val.begin(), val.end()), val.end());

  std::vector<long long> s(val.size());
  for (int i = 0; i < n; ++i) {
    a[i] = std::lower_bound(val.begin(), val.end(), a[i]) - val.begin();
    b[i] = std::lower_bound(val.begin(), val.end(), b[i]) - val.begin();
    s[a[i]] += 2 * w[i];
    s[b[i]] += 2 * w[i];
  }
  for (int i = 1; i < (int)val.size(); ++i) {
    s[i] += s[i - 1];
  }

  lichao_tree T;
  for (int i = 0; i < (int)val.size(); ++i) {
    T.insert(line(-4ll * val[i], s[i]));
  }
  long long ans = -INF;
  for (int i = 0; i < (int)val.size(); ++i) {
    ans = std::max(ans, T.query(val[i]) + s[i]);
  }
  std::cout << ans - 4 * std::accumulate(w.begin(), w.end(), 0ll) << "\n";
}
