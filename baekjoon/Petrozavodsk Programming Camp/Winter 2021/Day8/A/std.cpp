#include <bits/stdc++.h>

using matrix = std::array<std::array<int, 2>, 2>;

void get_coef(matrix w, matrix &A, matrix &B, matrix &C) {
  auto check = [&]() {
    if (C[0][0] * C[1][1] - C[0][1] * C[1][0] == 0) {
      return false;
    }
    for (int k = 0; k < 2; ++k) {
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          if (A[k][i] * B[k][j] != C[k][w[i][j]]) {
            return false;
          }
        }
      }
    }
    return true;
  };

  for (A[0][0] = -1; A[0][0] <= 1; ++A[0][0]) {
    for (A[0][1] = -1; A[0][1] <= 1; ++A[0][1]) {
      for (A[1][0] = -1; A[1][0] <= 1; ++A[1][0]) {
        for (A[1][1] = -1; A[1][1] <= 1; ++A[1][1]) {
          for (B[0][0] = -1; B[0][0] <= 1; ++B[0][0]) {
            for (B[0][1] = -1; B[0][1] <= 1; ++B[0][1]) {
              for (B[1][0] = -1; B[1][0] <= 1; ++B[1][0]) {
                for (B[1][1] = -1; B[1][1] <= 1; ++B[1][1]) {
                  for (C[0][0] = -1; C[0][0] <= 1; ++C[0][0]) {
                    for (C[0][1] = -1; C[0][1] <= 1; ++C[0][1]) {
                      for (C[1][0] = -1; C[1][0] <= 1; ++C[1][0]) {
                        for (C[1][1] = -1; C[1][1] <= 1; ++C[1][1]) {
                          if (check()) {
                            return;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

std::pair<int, matrix> inv(matrix A) {
  matrix res;
  res[0][0] = A[1][1];
  res[0][1] = -A[0][1];
  res[1][0] = -A[1][0];
  res[1][1] = A[0][0];
  return std::make_pair(A[0][0] * A[1][1] - A[0][1] * A[1][0], res);
}

using i64 = int64_t;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<matrix> w(n), A(n), B(n), C(n);
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    w[i][0][0] = s[0] - '0';
    w[i][0][1] = s[1] - '0';
    w[i][1][0] = s[2] - '0';
    w[i][1][1] = s[3] - '0';
    get_coef(w[i], A[i], B[i], C[i]);
  }
  std::vector<i64> f(1 << n), g(1 << n);
  for (auto &x : f) {
    std::cin >> x;
  }
  for (auto &x : g) {
    std::cin >> x;
  }

  auto FWT = [&](std::vector<i64> &f, const std::vector<matrix> &A) {
    for (int i = 0; i < n; ++i) {
      for (int S = 0; S < (1 << n); ++S) {
        if (S >> i & 1) {
          i64 p = f[S ^ (1 << i)], q = f[S];
          f[S ^ (1 << i)] = p * A[i][0][0] + q * A[i][0][1];
          f[S] = p * A[i][1][0] + q * A[i][1][1];
        }
      }
    }
  };

  auto IFWT = [&](std::vector<i64> &f, const std::vector<matrix> &A) {
    for (int i = 0; i < n; ++i) {
      auto [iv, IA] = inv(A[i]);
      for (int S = 0; S < (1 << n); ++S) {
        if (S >> i & 1) {
          i64 p = f[S ^ (1 << i)], q = f[S];
          f[S ^ (1 << i)] = (p * IA[0][0] + q * IA[0][1]) / iv;
          f[S] = (p * IA[1][0] + q * IA[1][1]) / iv;
        }
      }
    }
  };

  FWT(f, A);
  FWT(g, B);
  for (int i = 0; i < (1 << n); ++i) {
    f[i] *= g[i];
  }
  IFWT(f, C);
  for (int i = 0; i < (1 << n); ++i) {
    std::cout << f[i] << " ";
  }
  std::cout << "\n";
}
