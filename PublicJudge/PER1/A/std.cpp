#include <bits/stdc++.h>

class tree {
  int n, lg;
  std::vector<std::vector<int>> E;

  struct rooted {
    int rt;
    std::vector<int> dep, f;
    std::vector<std::vector<int>> val;
    std::vector<std::vector<int>> fa;
  };

  rooted st[2];

  std::pair<int, int> find_max(int u, int fa) {
    std::pair<int, int> max(0, u);
    for (int v : E[u]) {
      if (v != fa) {
        auto tmp = find_max(v, u);
        ++tmp.first;
        max = std::max(max, tmp);
      }
    }
    return max;
  }

public:
  tree(int t_n) : n(t_n), lg(std::__lg(n) + 1), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  void init() {
    st[0].rt = find_max(0, -1).second;
    st[1].rt = find_max(st[0].rt, -1).second;
    for (int k = 0; k < 2; ++k) {
      st[k].dep.assign(n, 0);
      st[k].f.assign(n, 0);
      st[k].val.assign(n, std::vector<int>(1, 0));
      st[k].fa.assign(n, std::vector<int>(lg, -1));

      auto dfs = [&](auto &self, int u) -> void {
        for (int i = 0; i + 1 < lg && st[k].fa[u][i] != -1; ++i) {
          st[k].fa[u][i + 1] = st[k].fa[st[k].fa[u][i]][i];
        }
        st[k].f[u] = 0;
        for (int v : E[u]) {
          if (v != st[k].fa[u][0]) {
            st[k].fa[v][0] = u;
            st[k].dep[v] = st[k].dep[u] + 1;
            self(self, v);
            st[k].f[u] = std::max(st[k].f[u], st[k].f[v] + 1);
            st[k].val[u].push_back(st[k].f[v] + 1);
          }
        }
        std::sort(st[k].val[u].begin(), st[k].val[u].end());
      };

      dfs(dfs, st[k].rt);
    }
  }

  int which(int u) const {
    return st[0].dep[u] > st[1].dep[u] ? 0 : 1;
  }

  int jump(int k, int u, int d) const {
    for (int i = 0; i < lg; ++i) {
      if (d >> i & 1) {
        u = st[k].fa[u][i];
      }
    }
    return u;
  }

  int father(int k, int u) const {
    return st[k].fa[u][0];
  }

  int max(int k, int u) const {
    return st[k].f[u];
  }

  const std::vector<int> &value(int k, int u) const {
    return st[k].val[u];
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  tree T(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    T.add_edge(u, v);
  }
  T.init();

  while (q--) {
    int u, d;
    std::cin >> u >> d;
    --u;
    int k = T.which(u);
    int h = (d - 1) / 2;
    int v = u;
    int ans = 0;
    if (h > 0) {
      v = T.jump(k, v, h - 1);
      ans = std::max(ans, T.max(k, v) + d - h + 1);
      v = T.father(k, v);
    }
    const auto &S = T.value(k, v);
    ans = std::max(ans, *--std::lower_bound(S.begin(), S.end(), d - h) + d - h);
    std::cout << ans << "\n";
  }
}
