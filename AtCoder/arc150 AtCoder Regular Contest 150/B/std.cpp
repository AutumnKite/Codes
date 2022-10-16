#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    long long A, B;
    std::cin >> A >> B;
    long long ans = A;
    for (long long x = A; x <= 100000; ++x) {
      ans = std::min(ans, x - A + (B + x - 1) / x * x - B);
    }
    for (long long k = 1; k <= 100000 && k * A <= 2000000000; ++k) {
      long long t = std::max((B + k - 1) / k, A);
      ans = std::min(ans, t - A + t * k - B);
    }
    std::cout << ans << "\n";
  }
}
