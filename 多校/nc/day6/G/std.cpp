#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  int W = 4 * n + 5, H = 13 * n + 19;
  std::vector<std::string> a(W, std::string(H, '.'));
  for (int i = 0; i < W; ++i) {
    a[i][0] = a[i][H - 1] = '*';
  }
  for (int i = 0; i < H; ++i) {
    a[0][i] = a[W - 1][i] = '*';
  }

  int r = n + 1, c = n + 2;
  for (int i = 0; i < 2 * n + 3; ++i) {
    a[r + i][c] = '@';
    a[r + i][c + 2 * n + 2] = '@';
    a[r + i][c + i] = '@';
  }
  c += 3 * n + 4;
  for (int i = 0; i < 2 * n + 3; ++i) {
    a[r + i][c] = '@';
    a[r][c + i] = '@';
    a[r + n + 1][c + i] = '@';
  }
  c += 3 * n + 4;
  for (int i = 0; i < 2 * n + 3; ++i) {
    a[r + i][c] = '@';
    a[r + 2 * n + 2][c + i] = '@';
  }
  c += 3 * n + 4;
  for (int i = 0; i < 2 * n + 3; ++i) {
    a[r][c + i] = '@';
    a[r + n + 1][c + i] = '@';
    a[r + 2 * n + 2][c + i] = '@';
    if (i < n + 1) {
      a[r + i][c] = '@';
    } else {
      a[r + i][c + 2 * n + 2] = '@';
    }
  }

  for (int i = 0; i < W; ++i) {
    std::cout << a[i] << "\n";
  }
}