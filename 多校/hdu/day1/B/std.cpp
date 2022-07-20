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
    int n, m, K;
    std::cin >> n >> m >> K;
    int sx, sy, tx, ty;
    std::cin >> sx >> sy >> tx >> ty;
    std::vector<int> lx(K), rx(K), ly(K), ry(K);
    for (int i = 0; i < K; ++i) {
      std::cin >> lx[i] >> ly[i] >> rx[i] >> ry[i];
      if (lx[i] > rx[i]) {
        std::swap(lx[i], rx[i]);
      }
      if (ly[i] > ry[i]) {
        std::swap(ly[i], ry[i]);
      }
    }
    int ans = K;
    for (int S = 0; S < (1 << K); ++S) {
      disjoint_set D(n * m);
      std::vector<std::vector<bool>> a(n + 1, std::vector<bool>(m));
      std::vector<std::vector<bool>> b(m + 1, std::vector<bool>(n));
      int cnt = 0;
      for (int i = 0; i < K; ++i) {
        if (S >> i & 1) {
          for (int j = ly[i]; j < ry[i]; ++j) {
            a[lx[i]][j] = true;
          }
          for (int j = lx[i]; j < rx[i]; ++j) {
            b[ly[i]][j] = true;
          }
        } else {
          ++cnt;
        }
      }
      for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          if (!a[i][j]) {
            D.merge((i - 1) * m + j, i * m + j);
          }
        }
      }
      for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          if (!b[i][j]) {
            D.merge(j * m + i - 1, j * m + i);
          }
        }
      }
      if (D.find(sx * m + sy) == D.find(tx * m + ty)) {
        ans = std::min(ans, cnt);
      }
    }
    std::cout << ans << "\n";
  }
}
