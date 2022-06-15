#include <bits/stdc++.h>

using u64 = uint64_t;
using u128 = __uint128_t;

u64 quick_power(u64 a, u64 b, u64 P) {
  u64 s = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      s = (u128)s * a % P;
    }
    a = (u128)a * a % P;
  }
  return s;
}

std::mt19937_64 rnd(std::chrono::system_clock::
                    now().time_since_epoch().count());

bool miller_rabin(u64 n) {
  if (n < 3 || n % 2 == 0) {
    return n == 2;
  }
  u64 a = n - 1;
  int b = 0;
  while (a % 2 == 0) {
    a /= 2, ++b;
  }
  for (int i = 0; i < 8; ++i) {
    u64 x = rnd() % (n - 2) + 2;
    u64 v = quick_power(x, a, n);
    if (v == 1) {
      continue;
    }
    bool ok = false;
    for (int j = 0; j < b; ++j) {
      if (v == n - 1) {
        ok = true;
        break;
      }
      v = (u128)v * v % n;
    }
    if (!ok) {
      return false;
    }
  }
  return true;
}

void pollard_rho(u64 n, std::vector<u64> &res) {
  if (n == 1) {
    return;
  }
  if (miller_rabin(n)) {
    res.push_back(n);
    return;
  }
  auto find = [&]() -> u64 {
    if (n == 4) {
      return 2;
    }
    while (true) {
      u64 c = rnd() % (n - 1) + 1;
      auto f = [&](u64 x) -> u64 {
        return ((u128)x * x + c) % n;
      };
      u64 t = 0, r = 0;
      do {
        u64 p = 1, q = 1;
        for (int i = 0; i < 128; ++i) {
          t = f(t), r = f(f(r));
          if (!(q = ((u128)t + n - r) * p % n)) {
            break;
          }
          p = q;
        }
        u64 d = std::gcd(p, n);
        if (d > 1) {
          return d;
        }
      } while (t != r);
    }
    return 1;
  };
  u64 d = find();
  pollard_rho(d, res);
  pollard_rho(n / d, res);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::map<u64, std::vector<std::pair<int, int>>> mp;
  for (int i = 0; i < n; ++i) {
    u64 x;
    std::cin >> x;
    std::vector<u64> p;
    pollard_rho(x, p);
    std::sort(p.begin(), p.end());
    p.erase(std::unique(p.begin(), p.end()), p.end());
    for (auto x : p) {
      if (mp[x].empty() || mp[x].back().first + 1 != i) {
        mp[x].emplace_back(i, 1);
      } else {
        ++mp[x].back().first;
        ++mp[x].back().second;
      }
    }
  }
  int ans = 0;
  for (auto [x, v] : mp) {
    for (auto [p, c] : v) {
      ans ^= c;
    }
  }
  if (ans == 0) {
    std::cout << "Second\n";
  } else {
    std::cout << "First\n";
  }
}
