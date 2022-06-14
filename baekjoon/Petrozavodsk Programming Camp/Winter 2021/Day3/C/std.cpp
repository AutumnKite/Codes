#include <bits/stdc++.h>

class basis {
  int n;
  std::vector<long long> a;

public:
  basis(int l) : n(l), a(n) {}

  void insert(long long x) {
    for (int i = n - 1; i >= 0; --i) {
      if (x >> i & 1) {
        if (!a[i]) {
          a[i] = x;
          return;
        }
        x ^= a[i];
      }
    }
  }

  long long query(long long x) const {
    for (int i = n - 1; i >= 0; --i) {
      if (x >> i & 1 && a[i]) {
        x ^= a[i];
      }
    }
    return x;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector<int> fa(n);
  std::vector<long long> fw(n);
  std::iota(fa.begin(), fa.end(), 0);
  basis B(60);

  std::function<int(int)> find = [&](int x) {
    if (fa[x] == x) {
      return x;
    }
    int fx = find(fa[x]);
    fw[x] ^= fw[fa[x]];
    return fa[x] = fx;
  };

  auto merge = [&](int x, int y, long long w) {
    int fx = find(x), fy = find(y);
    w ^= fw[x] ^ fw[y];
    if (fx == fy) {
      B.insert(w);
      return;
    }
    fa[fy] = fx;
    fw[fy] = w;
  };

  for (int i = 0; i < m; ++i) {
    int u, v;
    long long w;
    std::cin >> u >> v >> w;
    --u, --v;
    merge(u, v, w);
  }

  while (q--) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    find(u), find(v);
    std::cout << B.query(fw[u] ^ fw[v]) << "\n";
  }
}
