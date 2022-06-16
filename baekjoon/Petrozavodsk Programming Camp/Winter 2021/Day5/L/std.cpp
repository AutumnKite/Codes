#include <bits/stdc++.h>

const long double eps = 1e-13;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  long long n, m;
  std::cin >> n >> m;
  if (n > m) {
    std::swap(n, m);
  }

  long double sum = 1;
  long double now = 1;
  for (long long i = n + 1; i <= n + m; ++i) {
    now *= (n + m - i + 1);
    now /= i;
    sum += now;
    if (sum > 1e9) {
      std::cout << "Extreme Wealth\n";
      return 0;
    }
    if (now < eps) {
      break;
    }
  }
  now = 1;
  for (long long i = n - 1; i >= 0; --i) {
    now *= (i + 1);
    now /= (n + m - i);
    sum += now;
    if (sum > 1e9) {
      std::cout << "Extreme Wealth\n";
      return 0;
    }
    if (now < eps) {
      break;
    }
  }
  std::cout << sum << "\n";
}