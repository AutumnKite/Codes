#include <bits/stdc++.h>

using bint = __int128_t;

constexpr int N = 1000000;
constexpr bint mod = (29ll << 57) + 1, inv2 = (mod + 1) / 2;

bint qpow(bint a, bint b = mod - 2) {
  bint s = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      s = s * a % mod;
    }
    a = a * a % mod;
  }
  return s;
}

bool vis[N + 1];
std::vector<bint> prime;
bint inv[N + 1];

bint dfs(bint now, int k) {
  bint sum = now * (now + 1) / 2;
  while (k < (int)prime.size()) {
    bint p = prime[k];
    bint x = p * p;
    int z = 2;
    if (x > now) {
      break;
    }
    while (x <= now) {
      bint d = inv[z] + mod - inv[z - 1];
      sum = (sum + d * x % mod * dfs(now / x, k + 1)) % mod;
      x *= p;
      ++z;
    }
    ++k;
  }
  return sum;
}

void init() {
  for (int i = 2; i <= N; ++i) {
    if (!vis[i]) {
      prime.push_back(i);
    }
    for (int j = 0; j < (int)prime.size() && i * prime[j] <= N; ++j) {
      vis[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        break;
      }
    }
  }
  inv[1] = 1;
  for (int i = 2; i <= N; ++i) {
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  init();
  int T;
  std::cin >> T;
  while (T--) {
    long long n;
    std::cin >> n;
    std::cout << (long long)(dfs(n, 0) * qpow(n) % mod) << "\n";
  }
}
