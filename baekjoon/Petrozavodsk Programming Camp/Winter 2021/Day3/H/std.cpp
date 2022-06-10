#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> sta;
  std::vector<std::vector<int>> A(n), B(n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    while (a > 0) {
      int t = std::min(a, sta.back().second);
      sta.back().second -= t;
      a -= t;
      A[sta.back().first].push_back(i);
      B[i].push_back(sta.back().first);
      if (!sta.back().second) {
        sta.pop_back();
      }
    }
    if (b) {
      sta.emplace_back(i, b);
    }
  }

  std::vector<int> col(n);

  auto check = [&]() {
    col.assign(n, -1);

    auto dfs = [&](auto &self, int u, int c) -> bool {
      if (col[u] != -1) {
        return col[u] == c;
      }
      col[u] = c;
      for (int v : A[u]) {
        if (!self(self, v, c ^ 1)) {
          return false;
        }
      }
      for (int v : B[u]) {
        if (!self(self, v, c ^ 1)) {
          return false;
        }
      }
      return true;
    };

    for (int i = 0; i < n; ++i) {
      if (col[i] == -1) {
        if (!dfs(dfs, i, 0)) {
          return false;
        }
      }
    }
    return true;
  };

  if (check()) {
    std::cout << *std::max_element(col.begin(), col.end()) + 1 << "\n";
    for (int i = 0; i < n; ++i) {
      std::cout << col[i] + 1 << " \n"[i + 1 == n];
    }
    return 0;
  }

  auto solve = [&](auto &self, int l, int r) -> void {
    if (l == r) {
      return;
    }
    while (true) {
      int tl = l, tr = r;
      while (l + 1 < r) {
        while (!A[l].empty() && A[l].back() >= r) {
          A[l].pop_back();
        }
        if (A[l].empty()) {
          ++l;
          col[l] = col[l - 1];
        } else {
          break;
        }
      }
      while (l + 1 < r) {
        while (!B[r].empty() && B[r].back() <= l) {
          B[r].pop_back();
        }
        if (B[r].empty()) {
          --r;
          col[r] = col[r + 1];
        } else {
          break;
        }
      }
      if (tl == l && tr == r) {
        break;
      }
    }
    if (l + 1 == r) {
      return;
    }
    int lm = A[l].back(), rm = B[r].back();
    if (lm == rm) {
      col[lm] = col[l] ^ col[r] ^ 3;
    } else {
      col[lm] = col[r];
      col[rm] = col[l];
    }
    self(self, l, lm);
    self(self, lm, rm);
    self(self, rm, r);
  };

  col.assign(n, -1);
  col[0] = 0, col[n - 1] = 1;
  solve(solve, 0, n - 1);
  std::cout << 3 << "\n";
  for (int i = 0; i < n; ++i) {
    std::cout << col[i] + 1 << " \n"[i + 1 == n];
  }
}
