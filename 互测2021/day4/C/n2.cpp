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
  int sum = n - c;
  long long ans = 0;
  for (int v0 = 0; 2 * v0 <= sum; ++v0) {
    for (int v1 = v0; v1 <= v0 + 1 && v0 + v1 <= sum; ++v1) {
      if (x == 1 && v0 + v1 < sum) {
        continue;
      }
      auto [v, r] = calc(sum - (v0 + v1), x - 1);
      long long t = 1ll * (n + 1) * (n + 1);
      t -= 1ll * (v0 + 1) * (v0 + 1);
      t -= 1ll * (v1 + 1) * (v1 + 1);
      t -= 1ll * (v + 1) * (v + 1) * (x - 1 - r);
      t -= 1ll * (v + 2) * (v + 2) * r;
      t -= c - x;
      std::cerr << v0 << " " << v1 << " " << t << "\n";
      t /= 2;
      t += 1ll * (v0 + v1 + 2) * (k - 1);
      t -= 2ll * (sum + 1) * (k - 1);
      t -= 1ll * (c - k + 1) * (k - 1);
      t -= 1ll * k * (k - 1) / 2;
      ans = std::max(ans, t);
    }
  }
  std::cerr << k << " " << ans << "\n";
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
