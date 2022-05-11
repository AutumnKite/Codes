#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n, A;
  std::cin >> n >> A;

  auto mul = [&](long long x, long long y) {
    return y == 0 || x <= n / y ? x * y : n;
  };

  auto qpow = [&](long long a, int b) {
    long long s = 1;
    while (b) {
      if (b & 1) {
        s = mul(s, a);
      }
      a = mul(a, a);
      b >>= 1;
    }
    return s;
  };

  long long ans = n;
  for (int k = 1; k <= 50; ++k) {
    long long l = 0, r = n;
    while (l + 1 < r) {
      long long mid = (l + r) >> 1;
      if (qpow(mid, k) >= n) {
        r = mid;
      } else {
        l = mid;
      }
    }
    for (int i = 0; i <= k; ++i) {
      if (mul(qpow(l, i), qpow(r, k - i)) >= n) {
        ans = std::min(ans, l * i + r * (k - i) + (k - 1) * A);
      }
    }
  }
  std::cout << ans << "\n";
}
