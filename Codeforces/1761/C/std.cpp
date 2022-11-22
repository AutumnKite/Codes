#include <bits/stdc++.h>

using u128 = __uint128_t;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> E(n);
    std::vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
      std::string b;
      std::cin >> b;
      for (int j = 0; j < n; ++j) {
        if (b[j] == '1') {
          E[i].push_back(j);
          ++deg[j];
        }
      }
    }
    std::vector<u128> ans(n);
    std::vector<int> Q;
    for (int i = 0; i < n; ++i) {
      ans[i] |= (u128)1 << i;
      if (!deg[i]) {
        Q.push_back(i);
      }
    }
    for (int i = 0; i < (int)Q.size(); ++i) {
      int u = Q[i];
      for (int v : E[u]) {
        ans[v] |= ans[u];
        --deg[v];
        if (!deg[v]) {
          Q.push_back(v);
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      std::vector<int> res;
      for (int j = 0; j < n; ++j) {
        if (ans[i] >> j & 1) {
          res.push_back(j);
        }
      }
      std::cout << res.size();
      for (int x : res) {
        std::cout << " " << x + 1;
      }
      std::cout << "\n";
    }
  }
}
