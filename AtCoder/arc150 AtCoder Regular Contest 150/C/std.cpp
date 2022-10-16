#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  std::vector<int> a(n), b(k);
  for (int &x : a) {
    std::cin >> x;
  }
  for (int &x : b) {
    std::cin >> x;
  }
  b.push_back(-1);
  std::vector<int> dis(n, k + 1);
  std::vector<int> Q;
  dis[0] = a[0] == b[0];
  Q.push_back(0);
  for (int i = 0; i <= k; ++i) {
    for (int j = 0; j < (int)Q.size(); ++j) {
      int u = Q[j];
      for (int v : E[u]) {
        if (dis[v] == k + 1 && a[v] != b[dis[u]]) {
          dis[v] = dis[u];
          Q.push_back(v);
        }
      }
    }
    std::vector<int> nQ;
    for (int u : Q) {
      for (int v : E[u]) {
        if (dis[v] == k + 1) {
          dis[v] = dis[u] + 1;
          nQ.push_back(v);
        }
      }
    }
    Q.swap(nQ);
  }
  if (dis[n - 1] == k) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}
