#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
  freopen("seq.in", "w", stdout);

  int n = 100000;
  std::cout << n << " " << 50000000 << " " << 1 << "\n";
  std::vector<int> p(n);
  std::iota(p.begin(), p.end(), 1);
  std::shuffle(p.begin(), p.end(), rnd);
  for (int x : p) {
    std::cout << x << " ";
  }
  std::cout << "\n";
}
