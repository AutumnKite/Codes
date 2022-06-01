#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  std::vector<bool> vis(2 * m + 1);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    vis[a[i]] = true;
  }

  int l = std::__lg(2 * m);
  std::vector<int> L(2 * m + 1, 0), R(2 * m + 1, l);
  for (int i = 1; i <= 2 * m; i += 2) {
    while (R[i] >= 0 && ((1ll * i << R[i]) > 2 * m || !vis[i << R[i]])) {
      --R[i];
    }
    for (int j = 3 * i; j <= 2 * m; j += 2 * i) {
      R[j] = std::min(R[j], R[i] - 1);
    }
  }
  for (int i = 2 * m - 1; i >= 1; i -= 2) {
    for (int j = 3 * i; j <= 2 * m; j += 2 * i) {
      L[i] = std::max(L[i], L[j] + 1);
    }
    while (L[i] <= l && ((1ll * i << L[i]) > 2 * m || !vis[i << L[i]])) {
      ++L[i];
    }
  }
  bool ok = true;
  for (int i = 1; i <= 2 * m; i += 2) {
    ok &= L[i] <= R[i];
  }
  for (int i = 0; i < n; ++i) {
    int k = std::__lg(a[i] & -a[i]);
    int r = a[i] >> k;
    if (ok && L[r] <= k && k <= R[r]) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
}
