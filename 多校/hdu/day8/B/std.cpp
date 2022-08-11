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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    auto v = a;
    std::sort(v.begin(), v.end());
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
      a[i] = std::lower_bound(v.begin(), v.end(), a[i]) - v.begin();
      pos[a[i]] = i;
    }

    std::vector<mint> f(n + 1);

    std::function<void(int, int)> solve = [&](int l, int r) {
      if (l + 1 == r) {
        return;
      }
      int mid = (l + r) >> 1;
      solve(l, mid);
      std::vector<int> pmax(a.begin() + mid, a.begin() + r), pmin(pmax);
      for (int i = 1; i < r - mid; ++i) {
        pmax[i] = std::max(pmax[i], pmax[i - 1]);
        pmin[i] = std::min(pmin[i], pmin[i - 1]);
      }
      int max = 0, min = n;
      std::vector<std::array<mint, 4>> d(r - mid + 1);
      auto add = [&](int l, int r, int S, mint v) {
        d[l][S] += v;
        d[r][S] -= v;
      };
      for (int i = mid - 1, jmin = 0, jmax = 0; i >= l; --i) {
        max = std::max(max, a[i]);
        min = std::min(min, a[i]);
        while (jmin < r - mid && pmin[jmin] >= min) {
          ++jmin;
        }
        while (jmax < r - mid && pmax[jmax] <= max) {
          ++jmax;
        }
        if ((pos[min] - i) & 1 && !((pos[max] - i) & 1)) {
          int t = std::min(jmin, jmax);
          add(0, t, 0, f[i]);
          add(0, t, 1, f[i]);
          add(0, t, 2, f[i]);
          add(0, t, 3, f[i]);
        }
        if (jmin < jmax && !((pos[max] - i) & 1)) {
          add(jmin, jmax, !(i & 1), f[i]);
          add(jmin, jmax, (!(i & 1)) | 2, f[i]);
        }
        if (jmax < jmin && (pos[min] - i) & 1) {
          add(jmax, jmin, (i & 1) << 1, f[i]);
          add(jmax, jmin, (i & 1) << 1 | 1, f[i]);
        }
        add(std::max(jmax, jmin), r - mid, (i & 1) << 1 | !(i & 1), f[i]);
      }
      for (int i = 0; i < r - mid; ++i) {
        for (int j = 0; j < 4; ++j) {
          d[i + 1][j] += d[i][j];
        }
        f[mid + i + 1] += d[i][(pos[pmax[i]] & 1) << 1 | (pos[pmin[i]] & 1)];
      }
      solve(mid, r);
    };

    f[0] = 1;
    solve(0, n);
    std::cout << f[n] << "\n";
  }
}
