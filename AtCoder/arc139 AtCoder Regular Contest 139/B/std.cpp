#include <bits/stdc++.h>

using i64 = int64_t;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  i64 g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    i64 N, A, B, X, Y, Z;
    std::cin >> N >> A >> B >> X >> Y >> Z;
    i64 ans = N * X;
    Y = std::min(Y, A * X);
    Z = std::min(Z, B * X);

    auto calcA = [&](i64 i) {
      i64 M = N - i * A;
      if (M < 0) {
        return;
      }
      ans = std::min(ans, i * Y + (M / B) * Z + (M % B) * X);
    };

    auto calcB = [&](i64 i) {
      i64 M = N - i * B;
      if (M < 0) {
        return;
      }
      ans = std::min(ans, i * Z + (M / A) * Y + (M % A) * X);
    };

    if (std::min(A, B) <= 30000) {
      i64 x, y;
      i64 g = exgcd(A, B, x, y);
      i64 Ag = A / g, Bg = B / g;
      for (i64 i = 0; i < std::min(A, B); ++i) {
        i64 M = N - i;
        if (M % g == 0) {
          i64 nx = M / g * x, ny = M / g * y;
          i64 tx = (nx % Bg + Bg) % Bg, ty = (ny % Ag + Ag) % Ag;
          calcA(tx);
          calcB(ty);
        }
      }
    } else {
      for (i64 i = 0; i * A <= N; ++i) {
        calcA(i);
      }
    }
    std::cout << ans << "\n";
  }
}
