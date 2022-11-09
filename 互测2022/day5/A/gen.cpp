#include <bits/stdc++.h>

int main() {
  std::ofstream fout("path.in");

  fout << 5 << " " << 100 << " " << 40000000 << "\n";
  for (int test = 1; test <= 100; ++test) {
    int n = 49999;
    fout << n << "\n";
    for (int i = 1; i < n; ++i) {
      fout << i << " \n"[i == n - 1];
    }
  }
}
