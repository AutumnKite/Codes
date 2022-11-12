#include <bits/stdc++.h>

template<typename Val>
class fast_copy_array {
public:
  typedef std::size_t size_type;

protected:
  size_type n;

  struct node {
    node *ls, *rs;
    Val v;

    node() : ls(), rs(), v() {}
  };

  node *rt;

  void modify(node *&u, size_type l, size_type r, size_type x, const Val &v) {
    if (u == nullptr) {
      u = new node();
    } else {
      u = new node(*u);
    }
    if (l + 1 == r) {
      u->v = v;
      return;
    }
    size_type mid = (l + r) >> 1;
    if (x < mid) {
      modify(u->ls, l, mid, x, v);
    } else {
      modify(u->rs, mid, r, x, v);
    }
  }

  Val query(node *u, size_type l, size_type r, size_type x) const {
    if (u == nullptr) {
      return Val();
    }
    if (l + 1 == r) {
      return u->v;
    }
    size_type mid = (l + r) >> 1;
    if (x < mid) {
      return query(u->ls, l, mid, x);
    } else {
      return query(u->rs, mid, r, x);
    }
  }

public:
  fast_copy_array(size_type n) : n(n), rt(nullptr) {}

  void modify(size_type x, const Val &v) {
    modify(rt, 0, n, x, v);
  }

  Val query(size_type x) const {
    return query(rt, 0, n, x);
  }
};

class AC_automaton {
  int C, tot;
  std::vector<std::map<int, int>> son;
  std::vector<fast_copy_array<int>> trans;
  std::vector<int> fail;
  std::vector<int> sum;

  int new_node() {
    int u = tot++;
    son.emplace_back();
    trans.emplace_back(C);
    fail.emplace_back(-1);
    sum.emplace_back(0);
    return u;
  }

public:
  AC_automaton(int C) : C(C), tot() {
    new_node();
  }

  void insert(const std::vector<int> &a) {
    int u = 0;
    for (int x : a) {
      int &v = son[u][x];
      if (!v) {
        v = new_node();
      }
      u = v;
    }
    ++sum[u];
  }

  void build() {
    std::vector<int> Q;
    for (auto [c, v] : son[0]) {
      trans[0].modify(c, v);
      fail[v] = 0;
      Q.push_back(v);
    }
    for (int i = 0; i < (int)Q.size(); ++i) {
      int u = Q[i];
      trans[u] = trans[fail[u]];
      sum[u] += sum[fail[u]];
      for (auto [c, v] : son[u]) {
        trans[u].modify(c, v);
        fail[v] = trans[fail[u]].query(c);
        Q.push_back(v);
      }
    }
  }

  int total() const {
    return tot;
  }

  int next(int u, int c) const {
    return trans[u].query(c);
  }

  bool check(int u) const {
    return !sum[u];
  }
};

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::vector<std::pair<int, int>>> E(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    E[u].emplace_back(v, w);
  }
  AC_automaton A(n);
  for (int i = 0; i < k; ++i) {
    int c;
    std::cin >> c;
    std::vector<int> p(c);
    for (int j = 0; j < c; ++j) {
      std::cin >> p[j];
      --p[j];
    }
    A.insert(p);
  }
  A.build();

  std::vector<std::map<int, long long>> dis(n);
  std::vector<std::map<int, bool>> vis(n);
  std::vector<int> cnt(n);
  std::priority_queue<std::tuple<long long, int, int>> Q;
  int st = A.next(0, 0);
  dis[0][st] = 0;
  Q.emplace(0, 0, st);
  while (!Q.empty()) {
    auto [d, u, st] = Q.top();
    Q.pop();
    if (vis[u][st]) {
      continue;
    }
    if (u == n - 1) {
      std::cout << dis[u][st] << "\n";
      return 0;
    }
    vis[u][st] = true;
    ++cnt[u];
    if (cnt[u] >= 50) {
      continue;
    }
    for (auto [v, w] : E[u]) {
      int nx = A.next(st, v);
      if (A.check(nx) && (!dis[v].count(nx) || dis[u][st] + w < dis[v][nx])) {
        dis[v][nx] = dis[u][st] + w;
        Q.emplace(-dis[v][nx], v, nx);
      }
    }
  }
  std::cout << -1 << "\n";
}
