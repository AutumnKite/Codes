#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  long long sum = 1ll * n * n;
  std::vector<int> fa(n), fw(n), g(n, n);
  std::iota(fa.begin(), fa.end(), 0);

  std::function<int(int)> find = [&](int x) {
    if (fa[x] == x) {
      return x;
    }
    int fx = find(fa[x]);
    fw[x] = (fw[x] + fw[fa[x]]) % n;
    return fa[x] = fx;
  };

  auto merge = [&](int x, int y, int w) {
    int fx = find(x), fy = find(y);
    w = (w + fw[x] - fw[y] + n) % n;
    if (fx == fy) {
      sum -= g[fx];
      g[fx] = std::gcd(g[fx], w);
      sum += g[fx];
      return false;
    }
    sum -= g[fy];
    sum -= g[fx];
    fa[fy] = fx;
    fw[fy] = w;
    g[fx] = std::gcd(g[fx], g[fy]);
    sum += g[fx];
    return true;
  };

  while (q--) {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    merge((a - b + n) % n, (c - d + n) % n, (c - a + n) % n);
    std::cout << sum << "\n";
  }
}
