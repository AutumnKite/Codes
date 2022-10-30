#include <bits/stdc++.h>

void solve1(int n) {
  auto calc = [&](int i, int j) {
    int k = (i + j) % (2 * n + 1);
    if (k % 2 == 0) {
      return k / 2;
    } else {
      return (k + 2 * n + 1) / 2;
    }
  };
  auto ID = [&](int i, int c) {
    return i * 3 + c + 1;
  };
  for (int i = 0; i < 2 * n + 1; ++i) {
    std::cout << ID(i, 0) << " " << ID(i, 1) << " " << ID(i, 2) << "\n";
  }
  for (int i = 0; i < 2 * n + 1; ++i) {
    for (int j = i + 1; j < 2 * n + 1; ++j) {
      for (int k = 0; k < 3; ++k) {
        std::cout << ID(i, k) << " " << ID(j, k) << " "
                  << ID(calc(i, j), (k + 1) % 3) << "\n";
      }
    }
  }
}

void solve2(int n) {
  auto calc = [&](int i, int j) {
    int k = (i + j) % (2 * n);
    if (k % 2 == 0) {
      return k / 2;
    } else {
      return (k + 2 * n - 1) / 2;
    }
  };
  auto ID = [&](int i, int c) {
    return i * 3 + c + 1;
  };
  for (int i = 0; i < n; ++i) {
    std::cout << ID(i, 0) << " " << ID(i, 1) << " " << ID(i, 2) << "\n";
  }
  for (int i = 0; i < n; ++i) {
    for (int k = 0; k < 3; ++k) {
      std::cout << 6 * n + 1 << " " << ID(i, k) << " "
                << ID(n + i, (k + 2) % 3) << "\n";
    }
  }
  for (int i = 0; i < 2 * n; ++i) {
    for (int j = i + 1; j < 2 * n; ++j) {
      for (int k = 0; k < 3; ++k) {
        std::cout << ID(i, k) << " " << ID(j, k) << " "
                  << ID(calc(i, j), (k + 1) % 3) << "\n";
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  if (n % 6 == 3) {
    solve1(n / 6);
  } else {
    solve2(n / 6);
  }
}
