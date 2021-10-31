#include <bits/stdc++.h>

void solve(int l, int r) {
  if (l + 1 == r) {
    return;
  }
  int t = (r - l) / 3;
  for (int i = 0; i < t; ++i) {
    for (int j = 0; j < t; ++j) {
      std::cout << i + l + 1 << " ";
      std::cout << j + t + l + 1 << " ";
      std::cout << (i + j) % t + 2 * t + l + 1 << "\n";
    }
  }
  solve(l, l + t);
  solve(l + t, r - t);
  solve(r - t, r);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  solve(0, n);
}
