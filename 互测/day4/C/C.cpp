#include <bits/stdc++.h>

const int P = 998244353;

std::pair<int, int> calc(int a, int b) {
  if (b == 0) {
    return std::make_pair(0, a);
  }
  return std::make_pair(a / b, a % b);
}

long long solve(int n, int c, int k) {
  if (k == 0) {
    return 1ll * n * (n + 1) / 2;
  }
  int x = c / k;
  long long ans = 1ll * (n + 1) * (n + 1);
  int sum = n + 1 - (c - x);
  --k;
  if (sum - 2 * k >= x + 1) {
    auto [v, r] = calc(sum - 2 * k, x + 1);
    ans -= 1ll * v * v * (x + 1 - r);
    ans -= 1ll * (v + 1) * (v + 1) * r;
  } else {
    ans -= x - 1;
    int v0 = (sum - x + 1) / 2, v1 = sum - x + 1 - v0;
    ans -= 1ll * (v0 - k) * (v0 - k);
    ans -= 1ll * (v1 - k) * (v1 - k);
  }
  ans -= c - x;
  ans /= 2;
  ans += 1ll * k * k;
  ans -= 2ll * (n - c + 1) * k;
  ans -= 1ll * (c - k) * k;
  ans -= 1ll * k * (k + 1) / 2;
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, l, r, X;
  std::cin >> m >> l >> r >> X;
  std::string s;
  std::cin >> s;

  int n = X * m;
  for (int i = 0; i < m; ++i) {
    n += s[i] - '0';
  }

  int xor_sum = 0, pw = 1;
  int c = X * l;
  for (int k = 0; k < l; ++k) {
    c += s[k] - '0';
    pw = 233ll * pw % P;
  }
  for (int k = l; k <= r; ++k) {
    xor_sum ^= solve(n, c, k) % P * pw % P;
    if (k < m) {
      c += X + s[k] - '0';
      pw = 233ll * pw % P;
    }
  }
  std::cout << xor_sum << "\n";
}
