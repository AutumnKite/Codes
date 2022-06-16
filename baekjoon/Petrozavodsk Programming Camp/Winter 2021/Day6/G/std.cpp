#include <bits/stdc++.h>

constexpr int INF = std::numeric_limits<int>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i] >> b[i];
  }

  auto upd = [&](int &a, int b) {
    a = std::min(a, b);
  };
  
  std::vector<int> f(n, INF);
  f[0] = std::min(a[0], b[0]);
  for (int i = 1; i < n; ++i) {
    std::vector<int> g(n, INF);
    for (int j = 0; j < i; ++j) {
      upd(g[j + (a[i] * i < f[j])], f[j] + a[i]);
      upd(g[j + (b[i] * i < f[j])], f[j] + b[i]);
    }
    f.swap(g);
  }
  for (int i = 0; i < n; ++i) {
    if (f[i] < INF) {
      std::cout << i << "\n";
      return 0;
    }
  }
}
