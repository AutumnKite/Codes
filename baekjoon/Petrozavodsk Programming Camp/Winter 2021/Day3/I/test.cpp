#include <bits/stdc++.h>

int main() {
  std::ofstream fout("test.out");

  fout.setf(std::ios::fixed);
  fout.precision(6);

  for (int k = 0; k < 17; ++k) {
    for (int i = 100; i <= 5000000; i *= 1.25) {
      long double pw = 1.0;
      for (int j = 0; j < (1 << k); ++j) {
        pw *= 1.0 * (10000000 - i - j) / (10000000 - j);
      }
      fout << pw << " ";
    }
    fout << "\n";
  }
}
