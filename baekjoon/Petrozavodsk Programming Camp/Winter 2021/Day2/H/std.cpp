#include <bits/stdc++.h>

// bigint made by dengyaotriangle, modified by AutumnKite

#define __builtin_ia32_adc(x, y, flag) \
  __asm__(                             \
      "addb   %3, %0\n\t"              \
      "adcq   %2, %1\n\t"              \
      "setc   %0"                      \
      : "+r"(flag), "+r"(x)            \
      : "r"(y), "i"(-1)                \
      : "cc")

class bigint {
  using u64 = uint64_t;
  using u128 = __uint128_t;

  typedef std::size_t size_type;

  std::vector<u64> z;

public:
  bigint() {}

  bigint(u64 x) : z(x ? std::vector<u64>(1, x) : std::vector<u64>()) {}

  bigint(const std::string &s) {
    size_type pos = s.length();
    int cnt = 0;
    u64 val = 0;
    while (pos) {
      pos--;
      if (cnt == 64) {
        z.push_back(val);
        val = 0;
        cnt = 0;
      }
      val |= (u64)(s[pos] == '1') << cnt;
      ++cnt;
    }
    if (cnt && val) {
      z.push_back(val);
    }
  }

  explicit operator std::string() const {
    if (z.empty()) {
      return "0";
    }
    bool t = 0;
    std::string ret;
    for (int i = 63; i >= 0; --i) {
      t |= (z.back() >> i) & 1;
      if (t) {
        ret += '0' | ((z.back() >> i) & 1);
      }
    }
    for (size_type i = z.size() - 1; i--; ) {
      for (int j = 63; j >= 0; --j) {
        ret += '0' | ((z[i] >> j) & 1);
      }
    }
    return ret;
  }

  explicit operator bool() const {
    return !z.empty();
  }

  explicit operator u64() const {
    return z.empty() ? 0 : z[0];
  }

  size_type digit() const {
    if (z.empty()) {
      return 0;
    }
    return (z.size() << 6) - __builtin_clzll(z.back());
  }

  bool operator==(const bigint &rhs) const {
    return z == rhs.z;
  }

  bool operator!=(const bigint &rhs) const {
    return z != rhs.z;
  }

  bool operator<(const bigint &rhs) const {
    if (z.size() != rhs.z.size()) {
      return z.size() < rhs.z.size();
    }
    for (size_type i = z.size(); i--; ) {
      if (z[i] != rhs.z[i]) {
        return z[i] < rhs.z[i];
      }
    }
    return 0;
  }

  bool operator>(const bigint &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const bigint &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const bigint &rhs) const {
    return !(*this < rhs);
  }

  bigint &operator<<=(size_type n) {
    if (z.empty()) {
      return *this;
    }
    int w = n & 63;
    size_type k = n >> 6;
    size_type i = z.size();
    bool flag = false;
    if (w && (z.back() >> (64 - w))) {
      z.push_back(0);
      flag = true;
    }
    z.resize(z.size() + k);
    while (i--) {
      if (flag) {
        z[i + k + 1] |= z[i] >> (64 - w);
      }
      z[i + k] = z[i] << w;
      flag |= bool(w);
    }
    for (size_type i = 0; i < k; ++i) {
      z[i] = 0;
    }
    return *this;
  }

  bigint &operator>>=(size_type n) {
    int w = n & 63;
    size_type k = n >> 6, i = 0;
    for (; i + k < z.size(); ++i) {
      if (w && i) {
        z[i - 1] |= z[i + k] << (64 - w);
      }
      z[i] = z[i + k] >> w;
    }
    while (z.size() > i) {
      z.pop_back();
    }
    while (!z.empty() && z.back() == 0) {
      z.pop_back();
    }
    return *this;
  }

  bigint operator<<(size_type n) const {
    return bigint(*this) <<= n;
  }

  bigint operator>>(size_type n) const {
    return bigint(*this) >>= n;
  }

  bigint &operator+=(const bigint &rhs) {
    if (z.size() < rhs.z.size()) {
      z.resize(rhs.z.size());
    }
    bool carry = 0;
    for (size_type i = 0; i < z.size(); i++) {
      u64 rg = 0;
      if (i < rhs.z.size()) {
        rg = rhs.z[i];
      }
      __builtin_ia32_adc(z[i], rg, carry);
    }
    if (carry) {
      z.push_back(1);
    }
    return *this;
  }

  bigint &operator-=(const bigint &a) {
    bool carry = 1;
    for (size_type i = 0; i < z.size(); ++i) {
      u64 rg = -1;
      if (i < a.z.size()) {
        rg = ~a.z[i];
      }
      __builtin_ia32_adc(z[i], rg, carry);
    }
    while (!z.empty() && z.back() == 0) {
      z.pop_back();
    }
    return *this;
  }

  bigint &operator++() {
    return *this += bigint(1);
  }

  bigint &operator--() {
    return *this -= bigint(1);
  }

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

  bigint &operator*=(const bigint &rhs) {
    std::vector<u64> ret(z.size() + rhs.z.size());
    for (size_type i = 0; i < z.size(); ++i) {
      u64 carry = 0;
      bool wcarry = 0;
      size_type k = i;
      for (size_type j = 0; j < rhs.z.size(); ++j, ++k) {
        u128 r = z[i] * (u128)rhs.z[j] + carry;
        u64 cur = r;
        carry = r >> 64;
        __builtin_ia32_adc(ret[k], cur, wcarry);
      }
      while (carry || wcarry) {
        __builtin_ia32_adc(ret[k], carry, wcarry);
        carry = 0;
        ++k;
      }
    }
    while (!ret.empty() && ret.back() == 0) {
      ret.pop_back();
    }
    z = ret;
    return *this;
  }

  bigint &operator/=(const bigint &a) {
    if (a.digit() > digit()) {
      z.clear();
      return *this;
    }
    size_type k = digit() - a.digit() + 1;
    std::vector<u64> ret;
    while (k--) {
      bigint tmp = a << k;
      if (tmp <= *this) {
        *this -= tmp;
        size_type v = k >> 6;
        if (ret.size() <= v) {
          ret.resize(v + 1);
        }
        ret[v] |= (u64)(1) << (k & 63);
      }
    }
    z = ret;
    return *this;
  }

  bigint &operator%=(const bigint &a) {
    if (a.digit() > digit()) {
      return *this;
    }
    size_type k = digit() - a.digit() + 1;
    while (k--) {
      bigint tmp = a << k;
      if (tmp <= *this) {
        *this -= tmp;
      }
    }
    return *this;
  }

  bigint operator+(const bigint &rhs) const {
    return bigint(*this) += rhs;
  }

  bigint operator-(const bigint &rhs) const {
    return bigint(*this) -= rhs;
  }

  bigint operator*(const bigint &rhs) const {
    return bigint(*this) *= rhs;
  }

  bigint operator/(const bigint &rhs) const {
    return bigint(*this) /= rhs;
  }

  bigint operator%(const bigint &rhs) const {
    return bigint(*this) %= rhs;
  }
};

std::istream &operator>>(std::istream &in, bigint &a) {
  std::string s;
  in >> s;
  a = 0;
  for (char c : s) {
    a *= 10;
    a += c - '0';
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, bigint a) {
  std::string s;
  while (a) {
    s += uint64_t(a % 10) + '0';
    a /= 10;
  }
  std::reverse(s.begin(), s.end());
  if (s.empty()) {
    return out << 0;
  } else {
    return out << s;
  }
}

using i64 = int64_t;

constexpr i64 cyc[3] = {38247, 62231, 67876};

i64 exgcd(const i64 &a, const i64 &b, i64 &x, i64 &y) {
  if (!b) {
    x = 1, y = 0;
    return a;
  }
  i64 g = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return g;
}

i64 crt(i64 a, const i64 &p, i64 b, const i64 &q) {
  a %= p;
  b %= q;
  i64 x, y;
  assert(exgcd(p, q, x, y) == 1);
  x *= b - a;
  i64 res = p * x + a;
  res %= p * q;
  if (res < 0) {
    res += p * q;
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  i64 a, b;
  std::cin >> a >> b;

  std::cout << "? " << a << std::endl;
  bigint x;
  std::cin >> x;

  std::cout << "? " << b << std::endl;
  bigint y;
  std::cin >> y;

  std::vector<int> pos;
  std::vector<bigint> px(3), py(3);
  for (int i = 0; i < 3; ++i) {
    i64 p = cyc[i], q = cyc[(i + 1) % 3], r = cyc[(i + 2) % 3];
    if (a % p == b % p) {
      i64 k = a % p;
      while (k % q == a % q || k % q == b % q ||
             k % r == a % r || k % r == b % r) {
        k += p;
      }
      std::cout << "? " << k << std::endl;
      bigint t;
      std::cin >> t;
      px[i] = std::__gcd(t, x);
      py[i] = std::__gcd(t, y);
    } else {
      pos.push_back(i);
    }
  }

  for (int i = 0; i < (int)pos.size(); ++i) {
    int j = (i + 1) % pos.size();
    i64 p = cyc[pos[i]], q = cyc[pos[j]], r = cyc[pos[i] ^ pos[j] ^ 3];
    i64 k = crt(a, p, b, q);
    while (k % r == a % r || k % r == b % r) {
      k += p * q;
    }
    std::cout << "? " << k << std::endl;
    bigint t;
    std::cin >> t;
    px[pos[i]] = std::__gcd(t, x);
    py[pos[j]] = std::__gcd(t, y);
  }

  std::cout << "! " << std::accumulate(px.begin(), px.end(), bigint()) +
                       std::accumulate(py.begin(), py.end(), bigint()) << "\n";
}
