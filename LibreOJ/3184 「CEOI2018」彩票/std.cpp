#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, l;
  std::cin >> n >> l;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int q;
  std::cin >> q;
  std::vector<int> qk(q);
  for (int i = 0; i < q; ++i) {
    std::cin >> qk[i];
  }

  std::vector<std::vector<int>> ans(q, std::vector<int>(n - l + 1));

  std::vector<int> f(n + 1);
  for (int i = n - 1; i >= 0; --i) {
    std::vector<int> g(n + 1);
    for (int j = 0; j < n; ++j) {
      g[j] = f[j + 1] + (a[i] != a[j]);
      if (i + l < n && j + l < n) {
        g[j] -= a[i + l] != a[j + l];
      }
    }
    f.swap(g);
    if (i + l <= n) {
      std::vector<int> cnt(l + 1);
      for (int j = 0; j + l <= n; ++j) {
        ++cnt[f[j]];
      }
      for (int j = 1; j <= l; ++j) {
        cnt[j] += cnt[j - 1];
      }
      for (int j = 0; j < q; ++j) {
        ans[j][i] = cnt[qk[j]] - 1;
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    for (int j = 0; j + l <= n; ++j) {
      std::cout << ans[i][j] << " \n"[j + l == n];
    }
  }
}
