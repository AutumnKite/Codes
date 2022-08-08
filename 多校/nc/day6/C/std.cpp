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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::tuple<int, int, int>> edge;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int w;
      std::cin >> w;
      if (i < j && w) {
        edge.emplace_back(w, i, j);
      }
    }
  }
  std::sort(edge.begin(), edge.end());

  using state = std::array<mint, 2>;
  std::vector<state> f(1 << n);
  for (int i = 0; i < n; ++i) {
    f[1 << i] = {1, 0};
  }

  auto merge = [&](state a, state b, mint w) -> state {
    return {a[0] * b[0], a[0] * b[1] + a[1] * b[0] + w * a[0] * b[0]};
  };

  auto upd = [&](state &a, state b) {
    a[0] += b[0];
    a[1] += b[1];
  };

  for (auto [w, u, v] : edge) {
    mint mw = w;
    auto g = f;
    for (int S = 1 << u; S < (1 << n); S = (S + 1) | (1 << u)) {
      if (!(S >> v & 1)) {
        for (int T = S | (1 << v); T < (1 << n); T = (T + 1) | S | (1 << v)) {
          upd(g[T], merge(f[S], f[T ^ S], mw));
        }
      }
    }
    for (int S = 0; S < (1 << n); S = (S + 1) | (1 << u) | (1 << v)) {
      upd(g[S], f[S]);
    }
    f.swap(g);
  }

  std::vector<state> g = f;
  for (int S = 1; S < (1 << n); ++S) {
    int l = std::__lg(S);
    for (int T = S; T >= (1 << l); T = (T - 1) & S) {
      upd(g[S], merge(g[S ^ T], f[T], 0));
    }
  }
  std::cout << g.back()[1] << "\n";
}
