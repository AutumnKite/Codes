#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  int n, c, d;
  std::cin >> n >> c >> d;
  std::vector<std::vector<int>> a(n, std::vector<int>(c));
  std::vector<double> len(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < c; ++j) {
      std::cin >> a[i][j];
      len[i] += a[i][j] * a[i][j];
    }
    len[i] = sqrt(len[i]);
  }
  std::vector<std::vector<int>> b(n, std::vector<int>(d));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < d; ++j) {
      std::cin >> b[i][j];
    }
  }
  std::vector<std::vector<double>> f(c, std::vector<double>(d));
  for (int i = 0; i < c; ++i) {
    for (int j = 0; j < d; ++j) {
      for (int k = 0; k < n; ++k) {
        f[i][j] += a[k][i] * b[k][j] / len[k];
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int k = 0; k < d; ++k) {
      double res = 0;
      for (int j = 0; j < c; ++j) {
        res += a[i][j] * f[j][k];
      }
      std::cout << res / len[i] << " \n"[k == d - 1];
    }
  }
}
