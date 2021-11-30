#include <bits/stdc++.h>

const int P = 998244353;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    bool flag = true;
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
      flag &= a[i] == a[0];
    }

    if (flag) {
      int ans1 = 1, ans2 = 1;
      std::vector<std::vector<int>> C(n + 1, std::vector<int>(n + 1));
      for (int i = 0; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
          C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        }
      }
      for (int i = 0; i <= n / 2; ++i) {
        int s = 1;
        for (int j = 1; j <= i; ++j) {
          s = 1ll * s * (2 * i - 2 * j + 1) % P;
        }
        ans1 = (ans1 + 1ll * C[n][2 * i] * s) % P;
      }
      for (int i = 0; i < n - 1; ++i) {
        ans2 = 2 * ans2 % P;
      }
      std::cout << 1ll * (ans1 + ans2 - 1) * 499122177 % P << "\n";
      continue;
    }

    std::vector<bool> vis(n);
    std::vector<std::pair<int, int>> p;
    int ans = 0;

    auto dfs = [&](auto &self, bool par) -> void {
      ans += !par;
      for (int i = p.empty() ? 0 : p.back().first + 1; i < n; ++i) {
        if (!vis[i]) {
          for (int j = i + 1; j < n; ++j) {
            if (!vis[j] && a[i] == a[j]) {
              bool npar = par;
              for (auto [l, r] : p) {
                npar ^= i < r && r < j;
              }
              vis[i] = vis[j] = true;
              p.emplace_back(i, j);
              self(self, npar);
              p.pop_back();
              vis[i] = vis[j] = false;
            }
          }
        }
      }
    };

    dfs(dfs, false);
    std::cout << ans << "\n";
  }
}
/*
8
1
1
2
1 1
3
1 1 1
4
1 1 1 1
5
1 1 1 1 1
6
1 1 1 1 1 1
7
1 1 1 1 1 1 1
8
1 1 1 1 1 1 1 1
*/