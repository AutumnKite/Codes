#include <bits/stdc++.h>

double prob[17][48];

void init() {
  for (int k = 0; k < 17; ++k) {
    int idx = 0;
    for (int i = 100; i <= 5000000; i *= 1.25) {
      long double pw = 1.0;
      for (int j = 0; j < (1 << k); ++j) {
        pw *= 1.0 * (10000000 - i - j) / (10000000 - j);
      }
      prob[k][idx++] = pw;
    }
  }
}

int main() {

}
