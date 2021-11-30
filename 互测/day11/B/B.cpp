#ifndef __x86_64__
#error Only x86-64 targets are supported
#endif
#include <bits/stdc++.h>
#define __builtin_ia32_adc(x, y, flag)                                         \
  __asm__("addb   %3, %0\n\t"                                                  \
          "adcq   %2, %1\n\t"                                                  \
          "setc   %0"                                                          \
          : "+r"(flag), "+r"(x)                                                \
          : "r"(y), "i"(-1)                                                    \
          : "cc")

struct bigint { // made by dengyaotriangle!
  typedef unsigned long long u64;
  typedef unsigned __int128 u128;
  typedef std::size_t st;
  std::vector<u64> data;
  bigint() {}
  bigint(u64 x) : data(x ? std::vector<u64>{x} : std::vector<u64>{}) {}
  bigint(const std::string &s) {
    st pos = s.length();
    int cnt = 0;
    u64 val = 0;
    while (pos) {
      pos--;
      if (cnt == 64) {
        data.push_back(val);
        val = 0;
        cnt = 0;
      }
      val |= (u64)(s[pos] == '1') << cnt;
      ++cnt;
    }
    if (cnt && val)
      data.push_back(val);
  }
  explicit operator std::string() const {
    if (data.empty())
      return "0";
    bool t = 0;
    std::string ret;
    for (int i = 63; i >= 0; i--) {
      t |= (data.back() >> i) & 1;
      if (t)
        ret += '0' | ((data.back() >> i) & 1);
    }
    st i = data.size() - 1;
    while (i) {
      i--;
      for (int j = 63; j >= 0; j--)
        ret += '0' | ((data[i] >> j) & 1);
    }
    return ret;
  }
  explicit operator bool() const { return !data.empty(); }
  explicit operator u64() const { return data.empty() ? 0 : data[0]; }
  st digit() const {
    if (data.empty())
      return 0;
    return (data.size() << 6) - __builtin_clzll(data.back());
  }
  bool operator==(const bigint &a) const { return a.data == data; }
  bool operator!=(const bigint &a) const { return a.data != data; }
  bool operator<(const bigint &a) const {
    if (data.size() != a.data.size())
      return data.size() < a.data.size();
    for (st i = data.size(); i;) {
      i--;
      if (data[i] != a.data[i])
        return data[i] < a.data[i];
    }
    return 0;
  }
  bool operator>(const bigint &a) const { return a < (*this); }
  bool operator<=(const bigint &a) const { return !(*this > a); }
  bool operator>=(const bigint &a) const { return !(*this < a); }
  bigint &operator<<=(st n) {
    if (data.empty())
      return *this;
    int w = n & 63;
    st z = n >> 6;
    st i = data.size();
    bool flg = 0;
    if (w && (data.back() >> (64 - w)))
      data.push_back(0), flg = 1;
    data.resize(data.size() + z);
    while (i) {
      i--;
      if (flg)
        data[i + z + 1] |= data[i] >> (64 - w);
      data[i + z] = data[i] << w;
      flg |= bool(w);
    }
    for (st i = 0; i < z; i++)
      data[i] = 0;
    return *this;
  }
  bigint &operator>>=(st n) {
    int w = n & 63;
    st z = n >> 6, i = 0;
    for (; i + z < data.size(); i++) {
      if (w && i)
        data[i - 1] |= data[i + z] << (64 - w);
      data[i] = data[i + z] >> w;
    }
    while (data.size() > i)
      data.pop_back();
    while (!data.empty() && data.back() == 0)
      data.pop_back();
    return *this;
  }
  bigint operator<<(st n) const { return bigint(*this) <<= n; }
  bigint operator>>(st n) const { return bigint(*this) >>= n; }
  bigint &operator+=(const bigint &a) {
    data.resize(std::max(data.size(), a.data.size()));
    bool carry = 0;
    for (st i = 0; i < data.size(); i++) {
      u64 rg = 0;
      if (i < a.data.size())
        rg = a.data[i];
      __builtin_ia32_adc(data[i], rg, carry);
    }
    if (carry)
      data.push_back(1);
    return *this;
  }
  bigint &operator-=(const bigint &a) {
    bool carry = 1;
    for (st i = 0; i < data.size(); i++) {
      u64 rg = -1;
      if (i < a.data.size())
        rg = ~a.data[i];
      __builtin_ia32_adc(data[i], rg, carry);
    }
    while (!data.empty() && data.back() == 0)
      data.pop_back();
    return *this;
  }
  bigint &operator++() { return *this += bigint(1); }
  bigint &operator--() { return *this -= bigint(1); }
  bigint operator++(int) {
    bigint tmp = *this;
    ++*this;
    return tmp;
  }
  bigint operator--(int) {
    bigint tmp = *this;
    --*this;
    return tmp;
  }
  bigint &operator*=(const bigint &a) {
    std::vector<u64> ret(data.size() + a.data.size());
    for (st i = 0; i < data.size(); i++) {
      u64 carry = 0;
      bool wcarry = 0;
      st k = i;
      for (st j = 0; j < a.data.size(); j++, k++) {
        u128 r = data[i] * (u128)a.data[j] + carry;
        u64 cur = r;
        carry = r >> 64;
        __builtin_ia32_adc(ret[k], cur, wcarry);
      }
      while (carry || wcarry) {
        __builtin_ia32_adc(ret[k], carry, wcarry);
        carry = 0;
        k++;
      }
    }
    while (!ret.empty() && ret.back() == 0)
      ret.pop_back();
    data = ret;
    return *this;
  }
  bigint &operator/=(const bigint &a) {
    if (a.digit() > digit()) {
      data.clear();
      return *this;
    }
    st z = digit() - a.digit();
    std::vector<u64> ret;
    while (1) {
      bigint tmp = a << z;
      if (tmp <= *this) {
        *this -= tmp;
        st v1 = z >> 6;
        if (ret.size() <= v1)
          ret.resize(v1 + 1);
        ret[v1] |= (u64)(1) << (z & 63);
      }
      if (!z)
        break;
      z--;
    }
    data = ret;
    return *this;
  }
  bigint &operator%=(const bigint &a) {
    if (a.digit() > digit())
      return *this;
    st z = digit() - a.digit();
    while (1) {
      bigint tmp = a << z;
      if (tmp <= *this)
        *this -= tmp;
      if (!z)
        break;
      z--;
    }
    return *this;
  }
  bigint operator+(const bigint &a) const { return bigint(*this) += a; }
  bigint operator-(const bigint &a) const { return bigint(*this) -= a; }
  bigint operator*(const bigint &a) const { return bigint(*this) *= a; }
  bigint operator/(const bigint &a) const { return bigint(*this) /= a; }
  bigint operator%(const bigint &a) const { return bigint(*this) %= a; }
};
std::istream &operator>>(std::istream &st, bigint &a) {
  std::string s;
  st >> s;
  a = bigint(s);
  return st;
}
std::ostream &operator<<(std::ostream &st, const bigint &a) {
  return st << (std::string)(a);
}

using ull = unsigned long long;

ull quick_power(ull a, ull b, ull P) {
  ull s = 1;
  for (; b; b >>= 1) {
    if (b & 1) {
      s = (__uint128_t)s * a % P;
    }
    a = (__uint128_t)a * a % P;
  }
  return s;
}

std::mt19937_64 rnd(std::chrono::system_clock::
                    now().time_since_epoch().count());

bool miller_rabin(ull n) {
  if (n < 3 || n % 2 == 0) {
    return n == 2;
  }
  ull a = n - 1;
  int b = 0;
  while (a % 2 == 0) {
    a /= 2, ++b;
  }
  for (int i = 0; i < 8; ++i) {
    ull x = rnd() % (n - 2) + 2;
    ull v = quick_power(x, a, n);
    if (v == 1) {
      continue;
    }
    bool ok = false;
    for (int j = 0; j < b; ++j) {
      if (v == n - 1) {
        ok = true;
        break;
      }
      v = (__uint128_t)v * v % n;
    }
    if (!ok) {
      return false;
    }
  }
  return true;
}

void pollard_rho(ull n, std::vector<ull> &res) {
  if (n == 1) {
    return;
  }
  if (miller_rabin(n)) {
    res.push_back(n);
    return;
  }
  auto find = [&]() -> ull {
    if (n == 4) {
      return 2;
    }
    while (true) {
      ull c = rnd() % (n - 1) + 1;
      auto f = [&](ull x) -> ull {
        return ((__uint128_t)x * x + c) % n;
      };
      ull t = 0, r = 0;
      do {
        ull p = 1, q = 1;
        for (int i = 0; i < 128; ++i) {
          t = f(t), r = f(f(r));
          if (!(q = ((__uint128_t)t + n - r) * p % n)) {
            break;
          }
          p = q;
        }
        ull d = std::gcd(p, n);
        if (d > 1) {
          return d;
        }
      } while (t != r);
    }
    return 1;
  };
  ull d = find();
  pollard_rho(d, res);
  pollard_rho(n / d, res);
}

bigint bigint_sqrt(const bigint &N) {
  bigint l = 1, r = N + 1;
  while (l + 1 < r) {
    bigint mid = (l + r) / 2;
    if (mid * mid <= N) {
      l = mid;
    } else {
      r = mid;
    }
  }
  return l;
}

int main() {
  bigint N, M;
  std::cin >> N >> M;

  if (N.digit() <= 64) {
    ull n(N);
    std::vector<ull> res;
    pollard_rho(n, res);
    std::sort(res.begin(), res.end());
    std::cout << res.size() << "\n";
    for (auto x : res) {
      std::cout << bigint(x) << "\n";
    }
    return 0;
  }

  bigint S = N - M + 1;
  bigint p = (S + bigint_sqrt(S * S - N * 4)) / 2;
  bigint q = S - p;
  if (p > q) {
    std::swap(p, q);
  }
  std::cout << 2 << "\n" << p << "\n" << q << "\n";
}
