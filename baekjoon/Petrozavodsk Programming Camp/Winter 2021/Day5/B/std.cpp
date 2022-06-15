#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  int n;
  std::cin >> n;
  std::vector<double> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::sort(a.begin(), a.end());

  std::vector<double> f(1 << n);
  for (int S = 1; S < (1 << n); ++S) {
    int x = std::__lg(S);
    double now = 0, sum = 0, C = a[x];
    bool ok = false;
    for (int i = x; i >= 0; --i) {
      if (S >> i & 1) {
        double b = f[S ^ (1 << i)];
        if (C > a[i]) {
          double t = std::min(1 - now, (C - a[i]) * sum);
          now += t;
          C -= t / sum;
        }
        if (b >= a[i]) {
          ok = true;
          break;
        }
        sum += 1 / (a[i] - b);
      }
    }
    if (!ok) {
      double t = std::min(1 - now, C * sum);
      now += t;
      C -= t / sum;
    }
    f[S] = C;
  }
  std::cout << f.back() << "\n";
}
