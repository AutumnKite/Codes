#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
  std::ofstream fout("data.in");

  int T = 5;
  fout << T << "\n";
  while (T--) {
    int n = 100000, m = 200000, q = 100000;
    fout << n << " " << m << " " << q << "\n";
    std::vector<int> c;
    for (int i = 0; i < n; ++i) {
      c.push_back(i / 10);
    }
    std::shuffle(c.begin(), c.end(), rnd);
    for (int i = 0; i < n; ++i) {
      fout << c[i] + 1 << " \n"[i + 1 == n];
    }
    for (int i = 0; i < n; ++i) {
      fout << rnd() % 100000 + 1 << " \n"[i + 1 == n];
    }
    for (int i = 1; i < n; ++i) {
      fout << rnd() % i + 1 << " " << i + 1 << " " << rnd() % 100000 + 1 << "\n";
    }
    for (int i = 0; i < m - n + 1; ++i) {
      fout << rnd() % n + 1 << " " << rnd() % n + 1 << " " << rnd() % 100000 + 1 << "\n";
    }
    for (int i = 0; i < q; ++i) {
      fout << rnd() % 2 << " " << rnd() % n + 1 << " " << rnd() % 100000 + 1 << "\n";
    }
  }
}
