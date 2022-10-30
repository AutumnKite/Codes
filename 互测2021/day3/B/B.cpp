#include <bits/stdc++.h>

class set {
  int n, lg;
  std::vector<int> c;
  std::vector<int> sta;

public:
  set(int _n) : n(_n), lg(std::__lg(n)), c(n + 1) {
    for (int i = 1; i <= n; ++i) {
      c[i] = i & -i;
    }
  }

  void insert(int x) {
    sta.push_back(x);
    for (++x; x <= n; x += x & -x) {
      --c[x];
    }
  }

  void clear() {
    for (int x : sta) {
      for (++x; x <= n; x += x & -x) {
        ++c[x];
      }
    }
    sta.clear();
  }

  int mex(int k = 0) {
    int x = 0;
    int now = 0;
    for (int i = lg; i >= 0; --i) {
      int y = x + (1 << i);
      if (y <= n && now + c[y] <= k) {
        now += c[y];
        x = y;
      }
    }
    return x;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
  }
  std::vector<std::vector<int>> E(n);
  for (int i = 0; i < n; ++i) {
    int m;
    std::cin >> m;
    E[i].resize(m);
    for (int &x : E[i]) {
      std::cin >> x;
      --x;
    }
    std::reverse(E[i].begin(), E[i].end());
    if (E[i].empty()) {
      c[i] = 1;
    }
  }

  set S(400001);
  std::vector<std::array<int, 4>> g(n);
  for (int u = n - 1; u >= 0; --u) {
    if (c[u] == 1) {
      for (int d = 0; d < 4; ++d) {
        int now = d;
        for (int v : E[u]) {
          int sg = g[v][now];
          if (c[v] == 1) {
            sg = S.mex(sg);
          }
          if (sg < 2) {
            now |= 1 << sg;
          } else {
            S.insert(sg);
          }
        }
        if (now & 1) {
          S.insert(0);
        }
        if (now & 2) {
          S.insert(1);
        }
        g[u][d] = S.mex();
        S.clear();
      }
    } else {
      for (int d = 0; d < 2; ++d) {
        int now = d;
        for (int v : E[u]) {
          now = !g[v][now];
        }
        g[u][d] = g[u][d | 2] = now;
      }
    }
  }

  int k;
  std::cin >> k;
  int sg = 0;
  for (int i = 0; i < k; ++i) {
    int r;
    std::cin >> r;
    --r;
    sg ^= g[r][1];
  }
  if (sg) {
    std::cout << "Alice\n";
  } else {
    std::cout << "Bob\n";
  }
}
