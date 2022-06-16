#include <bits/stdc++.h>

using u64 = uint64_t;
using u128 = __uint128_t;

constexpr u64 P = 1000000000000000031;

u64 quick_power(u64 a, u64 b) {
  u64 s = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      s = (u128)s * a % P;
    }
    a = (u128)a * a % P;
  }
  return s;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  n = 1000000 - n;
  u64 s = 300;
  for (int i = 0; i < n; ++i) {
    s = quick_power(42, s);
  }
  std::cout << s << "\n";
}
