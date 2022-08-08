#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int A, B, C, x;
    std::cin >> A >> B >> C >> x;
    A -= B;
    if (x == C) {
      std::cout << "Yes\n";
      continue;
    }
    if (x == B - C) {
      std::cout << "Yes\n";
      continue;
    }
    if (x == A - C) {
      std::cout << "Yes\n";
      continue;
    }
    int t = A - B;
    if (t == 0) {
      std::cout << "No\n";
      continue;
    }
    if ((x - C) % t == 0 || (x - B + C) % t == 0 || (x - A + C) % t == 0) {
      std::cout << "Yes\n";
      continue;
    }
    std::cout << "No\n";
  }
}
