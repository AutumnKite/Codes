#include <bits/stdc++.h>

class disjoint_set {
public:
  typedef std::size_t size_type;

protected:
  std::vector<size_type> fa;

public:
  disjoint_set(size_type n = 0) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  size_type find(size_type x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
  }

  bool merge(size_type x, size_type y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    fa[y] = x;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> e(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        std::cin >> e[i][j];
      }
    }
    std::cout << n - 1 << "\n";
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        bool ok = true;
        for (int k = 0; k < n; ++k) {
          if (k != i && k != j) {
            ok &= e[i][j] != e[i][k] + e[k][j];
          }
        }
        if (ok) {
          std::cout << i + 1 << " " << j + 1 << "\n";
        }
      }
    }
  }
}
