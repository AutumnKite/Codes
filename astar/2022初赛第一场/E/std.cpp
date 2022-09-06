#include <bits/stdc++.h>

const int N = 2520, M = 2520 * 2 * 10;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long H;
  std::cin >> H;
  std::vector<long long> a(11);
  long long rem = 0;
  for (int i = 1; i <= 10; ++i) {
    std::cin >> a[i];
    int t = N / i;
    if (a[i] >= t) {
      long long c = a[i] / t - 1;
      rem += c;
      a[i] -= c * t;
    }
  }
  
  std::bitset<M + 1> f;
  f[0] = 1;
  for (int i = 1; i <= 10; ++i) {
    for (int j = 1; j <= a[i]; ++j) {
      f |= f << i;
    }
  }
  long long ans = 0;
  for (int i = 0; i <= M && i <= H; ++i) {
    if (f[i]) {
      ans = std::max(ans, i + std::min(rem, (H - i) / N) * N);
    }
  }
  std::cout << ans << "\n";
}
