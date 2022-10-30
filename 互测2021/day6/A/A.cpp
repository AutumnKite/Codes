#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P);

  using mint = modint<P>;

protected:
  unsigned v;

public:
  modint() : v() {}

  template<typename T, 
           typename std::enable_if<
                    std::is_signed<T>::value
                    && std::is_integral<T>::value,
                    bool>::type = true>
  modint(T _v) {
    long long tmp = _v % static_cast<long long>(P);
    if (tmp < 0) {
      tmp += P;
    }
    v = tmp;
  }

  template<typename T, 
           typename std::enable_if<
                    std::is_unsigned<T>::value
                    && std::is_integral<T>::value,
                    bool>::type = true>
  modint(T _v) {
    v = _v % P;
  }

  unsigned val() const {
    return v;
  }

  static constexpr unsigned mod() {
    return P;
  }

  static mint raw(unsigned v) {
    mint res;
    res.v = v;
    return res;
  }

  mint &operator+=(const mint &rhs) {
    v < P - rhs.v ? v += rhs.v : v -= P - rhs.v;
    return *this;
  }

  mint &operator++() {
    v + 1 < P ? ++v : v = 0;
    return *this;
  }

  mint operator++(int) {
    mint tmp = *this;
    v + 1 < P ? ++v : v = 0;
    return tmp;
  }

  mint &operator-=(const mint &rhs) {
    v < rhs.v ? v += P - rhs.v : v -= rhs.v;
    return *this;
  }

  mint &operator--() {
    v == 0 ? v = P - 1 : --v;
    return *this;
  }

  mint operator--(int) {
    mint tmp = *this;
    v == 0 ? v = P - 1 : --v;
    return tmp;
  }

  mint operator-() const {
    mint res;
    res.v = v == 0 ? 0 : P - v;
    return res;
  }

  mint &operator*=(const mint &rhs) {
    v = static_cast<unsigned long long>(v) * rhs.v % P;
    return *this;
  }

  mint pow(unsigned long long b) const {
    mint a(*this), s(1);
    for (; b; b >>= 1) {
      if (b & 1) {
        s *= a;
      }
      a *= a;
    }
    return s;
  }

  mint inv() const {
    return pow(P - 2);
  }

  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }

  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }

  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }

  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs.v == rhs.v;
  }

  friend bool operator!=(const mint &lhs, const mint &rhs) {
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

const int L = 13, N = 10000000;

long long pw[L + 1];
int len[N], sum[N];
std::pair<mint, mint> f[N];
mint pre[N];

void init() {
  pw[0] = 1;
  for (int i = 0; i < L; ++i) {
    pw[i + 1] = pw[i] * 10;
  }
  f[0].second = 1;
  for (int i = 1; i < N; ++i) {
    len[i] = len[i / 10] + 1;
    sum[i] = sum[i / 10] + i % 10;
    int j = i - sum[i];
    f[i].first = f[j].first + f[j].second * mint::raw(i);
    f[i].second = f[j].second * mint::raw(pw[len[i]]);
    pre[i] = pre[i - 1] + f[i].first;
  }
}

constexpr long long calc_sum(long long x) {
  if (x < N) {
    return sum[x];
  } else {
    return calc_sum(x / 10) + x % 10;
  }
}

constexpr long long calc_len(long long x) {
  if (x < N) {
    return len[x];
  } else {
    return calc_len(x / 10) + 1;
  }
}

std::pair<mint, mint> calc_f(long long i) {
  if (i < N) {
    return f[i];
  }
  long long j = i - calc_sum(i);
  auto fj = calc_f(j);
  std::pair<mint, mint> res;
  res.first = fj.first + fj.second * i;
  res.second = fj.second * pw[calc_len(i)];
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  init();

  int T;
  std::cin >> T;
  while (T--) {
    long long l, r;
    std::cin >> l >> r;
    if (r < N) {
      std::cout << pre[r] - pre[l - 1] << "\n";
    } else {
      mint ans = 0;
      for (long long i = l; i <= r; ++i) {
        ans += calc_f(i).first;
      }
      std::cout << ans << "\n";
    }
  }
}
