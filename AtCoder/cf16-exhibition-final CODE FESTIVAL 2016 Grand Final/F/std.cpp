#include <bits/stdc++.h>

constexpr long long INF = std::numeric_limits<long long>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<long long> L(n), R(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> L[i] >> R[i];
  }
  if (!(n & 1)) {
    L.push_back(0);
    R.push_back(0);
    ++n;
  }
  int m = (n - 1) / 2;

  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int x, int y) {
    return L[x] + R[x] > L[y] + R[y];
  });

  std::vector<std::array<long long, 2>> f(n + 1, {INF, INF});
  f[0][0] = 0;
  int cnt = 0;
  for (int i : id) {
    std::vector<std::array<long long, 2>> g(n + 1, {INF, INF});
    for (int l = 0; l <= cnt; ++l) {
      for (int k = 0; k <= 1 && l + k <= cnt; ++k) {
        int r = cnt - l - k;
        g[l][k] = std::min(g[l][k], f[l][k] + L[i] + (L[i] + R[i]) * r);
        g[l + 1][k] = std::min(g[l + 1][k], f[l][k] + R[i] + (L[i] + R[i]) * l);
        if (k == 0) {
          g[l][1] = std::min(g[l][1], f[l][0] + (L[i] + R[i]) * m);
        }
      }
    }
    ++cnt;
    f.swap(g);
  }
  std::cout << f[m][1] << "\n";
}
