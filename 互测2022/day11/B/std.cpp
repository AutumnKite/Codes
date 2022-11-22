#include "pilgrimage.h"
#include <bits/stdc++.h>

using i64 = int64_t;

int exgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  int g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

int inv(int n, int mod) {
  int x, y;
  exgcd(n, mod, x, y);
  return (x += mod) >= mod ? x - mod : x;
}

int power(int a, i64 b, int mod) {
  int s = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      s = (i64)s * a % mod;
    }
    a = (i64)a * a % mod;
  }
  return s;
}

int mod, inv4;
std::vector<std::pair<int, int>> pf;
std::vector<int> coef, phi;
std::vector<std::vector<int>> f;
std::vector<std::vector<int>> iv;
std::vector<std::vector<int>> pw;

void init_f(int i) {
  auto [p, pk] = pf[i];
  coef[i] = inv(mod / pk, pk) * (mod / pk) % mod;
  f[i].resize(pk + 1);
  f[i][0] = 1;
  for (int k = 1; k <= pk; ++k) {
    f[i][k] = (i64)f[i][k - 1] * (k % p == 0 ? 1 : k) % pk;
  }
  iv[i].resize(pk);
  for (int k = 1; k < pk; ++k) {
    if (k % p) {
      iv[i][k] = inv(k, pk);
    }
  }
  phi[i] = pk / p * (p - 1);
  pw[i].resize(phi[i]);
  pw[i][0] = 1;
  for (int k = 1; k < phi[i]; ++k) {
    pw[i][k] = (i64)pw[i][k - 1] * f[i][pk] % pk;
  }
}

int fac(i64 n, int i) {
  auto [p, pk] = pf[i];
  int res = 1;
  while (n) {
    res = (i64)res * pw[i][(n / pk) % phi[i]] % pk * f[i][n % pk] % pk;
    n /= p;
  }
  return res;
}

int binom_(i64 n, int i) {
  auto [p, pk] = pf[i];
  if (p == pk) {
    int up = 1, dw = 1;
    while (n) {
      int t = n % p;
      if (t * 2 >= p) {
        return 0;
      }
      up = (i64)up * f[i][2 * t] % p;
      dw = (i64)dw * f[i][t] % p;
      n /= p;
    }
    dw = iv[i][dw];
    return (i64)up * dw % p * dw % p;
  }
  i64 k = 0;
  for (i64 x = 2 * n; x; x /= p) k += x / p;
  for (i64 x = n; x; x /= p) k -= x / p * 2;
  if (k >= 20) {
    return 0;
  }
  int up = fac(2 * n, i), dw = iv[i][fac(n, i)];
  return (i64)up * dw % pk * dw % pk * power(p, k, pk) % pk;
}

int binom(i64 n) {
  int res = 0;
  for (int i = 0; i < (int)pf.size(); ++i) {
    int v = binom_(n, i);
    res = (res + (i64)v * coef[i]) % mod;
  }
  return res;
}

void init(int o, int p) {
  pf.clear();
  mod = p;
  for (int i = 2; i * i <= p; ++i) {
    if (p % i == 0) {
      int pk = 1;
      while (p % i == 0) {
        p /= i;
        pk *= i;
      }
      pf.emplace_back(i, pk);
    }
  }
  if (p > 1) {
    pf.emplace_back(p, p);
  }
  coef.resize(pf.size());
  phi.resize(pf.size());
  f.resize(pf.size());
  iv.resize(pf.size());
  pw.resize(pf.size());
  for (int i = 0; i < (int)pf.size(); ++i) {
    init_f(i);
  }
  inv4 = inv(4, mod);
}

int ask(long long n) {
  return n % mod * binom(n) % mod * power(inv4, n, mod) % mod;
}
