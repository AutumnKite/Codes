#include <bits/stdc++.h>

const char dir_name[] = "UDLR";
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> U(n), D(n), L(n), R(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> U[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> D[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> L[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> R[i];
  }

  std::vector<int> rem(n);
  for (int i = 0; i < n; ++i) {
    rem[i] = n - U[i] - D[i];
    if (rem[i] < 0) {
      std::cout << "NO\n";
      return 0;
    }
  }
  std::vector<std::vector<int>> dir(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin(), id.end(), [&](int x, int y) {
      return rem[x] > rem[y];
    });
    if (L[i] + R[i] > n) {
      std::cout << "NO\n";
      return 0;
    }
    for (int j = 0; j < L[i] + R[i]; ++j) {
      if (rem[id[j]]) {
        --rem[id[j]];
        dir[i][id[j]] = 2;
      } else {
        std::cout << "NO\n";
        return 0;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    int idx = 0;
    for (int j = 0; j < n; ++j) {
      if (dir[i][j] == 2) {
        dir[i][j] += idx >= L[i];
        ++idx;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    int idx = 0;
    for (int j = 0; j < n; ++j) {
      if (dir[j][i] == 0) {
        dir[j][i] += idx >= U[i];
        ++idx;
      }
    }
  }

  std::vector<std::vector<bool>> vis(n, std::vector<bool>(n)), ok(vis);

  auto dfs = [&](auto &self, int x, int y) -> bool {
    if (ok[x][y]) {
      return false;
    }
    if (vis[x][y]) {
      vis[x][y] = false;
      return true;
    }
    vis[x][y] = true;
    int tmp = dir[x][y];
    int X = x, Y = y;
    while (true) {
      X += dx[tmp], Y += dy[tmp];
      if (X < 0 || X >= n || Y < 0 || Y >= n) {
        break;
      }
      if (self(self, X, Y)) {
        dir[X][Y] = tmp;
        if (vis[x][y]) {
          vis[x][y] = false;
          return true;
        } else {
          return self(self, x, y);
        }
      }
    }
    ok[x][y] = true;
    std::cout << dir_name[tmp] << (tmp < 2 ? y : x) + 1 << "\n";
    return false;
  };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      dfs(dfs, i, j);
    }
  }
}
