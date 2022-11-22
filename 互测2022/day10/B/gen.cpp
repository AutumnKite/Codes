#include <bits/stdc++.h>

std::mt19937_64 rnd(time(0));

int main() {
  std::ofstream fout("B.in");

  fout << "0 1000000 765765\n";
  for (int i = 0; i < 1000000; ++i) {
    fout << rnd() % (long long)(1e18) + 1 << "\n";
  }
}
