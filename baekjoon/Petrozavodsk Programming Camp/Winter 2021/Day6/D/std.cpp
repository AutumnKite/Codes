#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  int cnt[2] = {};
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    ++cnt[a[i] & 1];
  }

  if (cnt[0] > 1 || cnt[1] > 3) {
    std::cout << "Yes\n";
    return 0;
  }

  for (int S = 1; S < (1 << n); ++S) {
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
      if (S >> i & 1) {
        sum += a[i];
      }
    }
    for (int i = 2; 1ll * i * i <= sum; ++i) {
      if (sum % i == 0) {
        std::cout << "Yes\n";
        return 0;
      }
    }
  }
  std::cout << "No\n";
}
