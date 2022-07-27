#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
  std::ofstream fout("data.in");

  int T = 3;
  fout << T << "\n";
  while (T--) {
    int n = 100000, q = 100000;
    fout << n << " " << q << "\n";
    for (int i = 0; i < n; ++i) {
      fout << rnd() % 100000000 + 1 << " ";
      fout << rnd() % 100000000 + 1 << "\n";
    }
    while (q--) {
      int op = rnd() % 2 + 1;
      fout << op << " ";
      if (op == 1) {
        fout << rnd() % n + 1 << " ";
        fout << rnd() % 100000000 + 1 << " ";
        fout << rnd() % 100000000 + 1 << "\n";
      } else {
        int l = rnd() % n + 1, r = rnd() % n + 1;
        if (l > r) {
          std::swap(l, r);
        }
        fout << l << " " << r << "\n";
      }
    }
  }
}
