#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 1; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  std::vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
  }
  std::vector<int> d(m);
  for (int i = 1; i < m; ++i) {
    std::cin >> d[i];
  }

  long long ans = 0;
  for (int i = 1; i < m; ++i) {
    ans += c[0] + d[i];
  }
  std::vector<int> id(m - 1);
  std::iota(id.begin(), id.end(), 1);
  std::sort(id.begin(), id.end(), [&](int i, int j) {
    return b[i] - d[i] < b[j] - d[j];
  });
  std::vector<long long> sum_b(m), sum_d(m);
  for (int i = 0; i < m - 1; ++i) {
    sum_b[i + 1] = sum_b[i] + b[id[i]];
    sum_d[i + 1] = sum_d[i] + d[id[i]];
  }
  for (int i = 1; i < n; ++i) {
    int p = std::lower_bound(id.begin(), id.end(), c[i] - a[i], [&](int j, int v) {
      return b[j] - d[j] < v;
    }) - id.begin();
    ans += 1ll * p * a[i] + sum_b[p];
    ans += 1ll * (m - 1 - p) * c[i] + sum_d[m - 1] - sum_d[p];
    ans += a[i] + b[0];
  }
  std::cout << ans << "\n";
}
