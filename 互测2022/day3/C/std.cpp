#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P, "P must be a positive integer");

  using mint = modint<P>;

protected:
  unsigned v;

public:
  constexpr modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  constexpr modint(T t_v) : v() {
    long long tmp = t_v % static_cast<long long>(P);
    if (tmp < 0) {
      tmp += P;
    }
    v = tmp;
  }

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_unsigned<T>::value,
                                   bool>::type = true>
  constexpr modint(T t_v) : v() {
    v = t_v % P;
  }

  constexpr unsigned val() const {
    return v;
  }

  static constexpr unsigned mod() {
    return P;
  }

  static constexpr mint raw(unsigned v) {
    mint res;
    res.v = v;
    return res;
  }

  constexpr mint &operator+=(const mint &rhs) {
    v < P - rhs.v ? v += rhs.v : v -= P - rhs.v;
    return *this;
  }

  constexpr mint &operator++() {
    v + 1 < P ? ++v : v = 0;
    return *this;
  }

  constexpr mint operator++(int) {
    mint tmp = *this;
    v + 1 < P ? ++v : v = 0;
    return tmp;
  }

  constexpr mint &operator-=(const mint &rhs) {
    v < rhs.v ? v += P - rhs.v : v -= rhs.v;
    return *this;
  }

  constexpr mint &operator--() {
    v ? --v : v = P - 1;
    return *this;
  }
  
  constexpr mint operator--(int) {
    mint tmp = *this;
    v ? --v : v = P - 1;
    return tmp;
  }

  constexpr mint operator-() const {
    mint res;
    res.v = v ? P - v : 0;
    return res;
  }

  constexpr mint &operator*=(const mint &rhs) {
    v = static_cast<unsigned long long>(v) * rhs.v % P;
    return *this;
  }

  constexpr mint pow(unsigned long long b) const {
    mint a(*this), s(1);
    for (; b; b >>= 1) {
      if (b & 1) {
        s *= a;
      }
      a *= a;
    }
    return s;
  }

  constexpr mint inv() const {
    return pow(P - 2);
  }

  constexpr friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }

  constexpr friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }

  constexpr friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }

  constexpr friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs.v == rhs.v;
  }

  constexpr friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs.v != rhs.v;
  }

  friend std::istream &operator>>(std::istream &in, mint &x) {
    return in >> x.v;
  }

  friend std::ostream &operator<<(std::ostream &out, const mint &x) {
    return out << x.v;
  }
};

using mint = modint<998244353>;
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

mint calc(u64 n, u64 r) {
  if (n == 2) {
    return r == 0 ? 20 : 8;
  }
  mint w = n;
  if (r != 0) {
    return w * w * w + (n % 4 == 1 ? -1 : 1);
  }
  mint c0 = n % 4 == 1 ? 2 * w - 1 : 1;
  return 3 * w * w * w - w * w - w + (w - 1) * (w - 1) * c0;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  u64 n, r;
  std::cin >> n >> r;
  std::vector<u64> pf;
  pollard_rho(n, pf);
  mint ans = 1;
  for (u64 p : pf) {
    ans *= calc(p, r % p);
  }
  std::cout << ans << "\n";
}
