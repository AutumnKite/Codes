#include <bits/stdc++.h>

using i64 = int64_t;

std::mt19937_64 rnd(time(0));

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  i64 P;
  std::cin >> n >> P;
  std::vector<i64> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::map<i64, i64> mp;
  while (true) {
    i64 mask = rnd() % (1ll << n);
    i64 sum = 0;
    for (int i = 0; i < n; ++i) {
      if (mask >> i & 1) {
        sum += a[i];
      }
    }
    sum %= P;
    if (mp.count(sum) && mp[sum] != mask) {
      i64 other = mp[sum];
      for (int i = 0; i < n; ++i) {
        if ((mask ^ other) >> i & 1) {
          if (mask >> i & 1) {
            std::cout << 1;
          } else {
            std::cout << -1;
          }
        } else {
          std::cout << 0;
        }
        std::cout << " \n"[i == n - 1];
      }
      return 0;
    }
    mp[sum] = mask;
  }
}
