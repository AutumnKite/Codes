#include <bits/stdc++.h>

struct frac {
  int a, b;

  frac() : a(), b() {}

  frac(int t_a, int t_b) : a(t_a), b(t_b) {}
  
  bool operator<(const frac &rhs) const {
    return 1ll * a * rhs.b < 1ll * rhs.a * b;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  std::string a;
  std::cin >> a;

  std::vector<int> s(n + 1);
  for (int i = 0; i < n; ++i) {
    s[i + 1] = s[i] + (a[i] - '0');
  }

  std::vector<frac> f;
  for (int i = 1; i <= 1000000; ++i) {
    f.emplace_back(i / n * s[n] + s[i % n], i);
  }

  auto cmp = [&](const frac &a, const frac &b) {
    if (a < b) {
      return false;
    }
    if (b < a) {
      return true;
    }
    return a.b < b.b;
  };

  std::sort(f.begin(), f.end(), cmp);

  while (q--) {
    int op, k;
    std::cin >> op >> k;
    if (op == 1) {
      std::cout << f[k - 1].b << "\n";
    } else {
      frac t = frac(k / n * s[n] + s[k % n], k);
      if (!(frac(s[n], n) < t)) {
        std::cout << "inf\n";
      } else {
        std::cout << std::lower_bound(f.begin(), f.end(), t, cmp) - f.begin() + 1 << "\n";
      }
    }
  }
}
