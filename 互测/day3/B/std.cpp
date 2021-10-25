#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
  }
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < n; ++i) {
    int m;
    std::cin >> m;
    E[i].resize(m);
    for (int &x : E[i]) {
      std::cin >> x;
      --x;
    }
  }

  if (std::accumulate(c.begin(), c.end(), 0) == 0) {
    std::vector<int> s(n);
    for (int i = n - 1; i >= 0; --i) {
      s[i] ^= 1;
      for (int v : E[i]) {
        s[i] ^= s[v];
      }
    }
    int k;
    std::cin >> k;
    int sg = 0;
    for (int i = 0; i < k; ++i) {
      int r;
      std::cin >> r;
      --r;
      sg ^= s[r];
    }
    if (sg) {
      std::cout << "Alice\n";
    } else {
      std::cout << "Bob\n";
    }
    return 0;
  }

  std::vector<bool> vis(n);
  std::vector<int> f(n);

  auto dfs = [&](auto &self, int u, int nxt) -> void {
    vis[u] = true;
    std::set<int> S;
    std::reverse(E[u].begin(), E[u].end());
    if (nxt != -1) {
      S.insert(f[nxt]);
    }
    int lst = nxt;
    for (int v : E[u]) {
      self(self, v, lst);
      S.insert(f[v]);
      lst = v;
    }
    f[u] = 0;
    while (S.count(f[u])) {
      ++f[u];
    }
  };

  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      dfs(dfs, i, -1);
    }
  }

  int k;
  std::cin >> k;
  int sg = 0;
  for (int i = 0; i < k; ++i) {
    int r;
    std::cin >> r;
    --r;
    sg ^= f[r];
  }
  if (sg) {
    std::cout << "Alice\n";
  } else {
    std::cout << "Bob\n";
  }
}
