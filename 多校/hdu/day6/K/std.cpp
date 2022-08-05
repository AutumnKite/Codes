#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P, "P must be a positive integer");

  using mint = modint<P>;

protected:
  unsigned v;

public:
  modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  modint(T t_v) : v() {
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
  modint(T t_v) : v() {
    v = t_v % P;
  }

  unsigned val() const {
    return v;
  }

  static unsigned mod() {
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
    v ? --v : v = P - 1;
    return *this;
  }
  
  mint operator--(int) {
    mint tmp = *this;
    v ? --v : v = P - 1;
    return tmp;
  }

  mint operator-() const {
    mint res;
    res.v = v ? P - v : 0;
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

const int N = 100000;

std::vector<int> prime;
bool vis[N + 1];
int phi[N + 1];

void init() {
  phi[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (!vis[i]) {
      prime.push_back(i);
      phi[i] = i - 1;
    }
    for (int x : prime) {
      if (i * x > N) {
        break;
      }
      vis[i * x] = true;
      if (i % x == 0) {
        phi[i * x] = phi[i] * x;
        break;
      } else {
        phi[i * x] = phi[i] * (x - 1);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  init();
  while (T--) {
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
      inv[i] = -inv[mint::mod() % i] * (mint::mod() / i);
    }
    std::vector<mint> g(n + 1);
    for (int i = 1; i <= n; ++i) {
      g[i] = std::__gcd(m, i) * mint::raw(phi[i]);
    }
    std::vector<mint> ans(n + 1);
    mint pw = 1;
    for (int i = 1; i <= n; ++i) {
      pw *= m;
      for (int j = i; j <= n; j += i) {
        ans[j] += g[j / i] * pw;
      }
    }
    mint invm = mint(m).inv();
    for (int i = 1; i <= n; ++i) {
      std::cout << ans[i] * inv[i] * invm << " \n"[i == n];
    }
  }
}
