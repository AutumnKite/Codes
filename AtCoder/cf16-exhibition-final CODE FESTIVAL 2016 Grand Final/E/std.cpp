#include <bits/stdc++.h>

class disjoint_set {
public:
  typedef std::size_t size_type;

protected:
  std::vector<size_type> fa;

public:
  disjoint_set(size_type n = 0) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  size_type find(size_type x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
  }

  bool merge(size_type x, size_type y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    fa[y] = x;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed);
  std::cout.precision(12);

  int n;
  std::cin >> n;
  std::vector<int> x(n), y(n), a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x[i] >> y[i] >> a[i];
  }

  auto dist = [&](int i, int j) {
    return sqrt(1ll * (x[i] - x[j]) * (x[i] - x[j]) +
                1ll * (y[i] - y[j]) * (y[i] - y[j]));
  };

  std::vector<double> MST(1 << n);
  std::vector<double> sum(1 << n);
  std::vector<int> cnt(1 << n);
  for (int S = 1; S < (1 << n); ++S) {
    std::vector<int> id;
    for (int i = 0; i < n; ++i) {
      if (S >> i & 1) {
        id.push_back(i);
        sum[S] += a[i];
        ++cnt[S];
      }
    }
    disjoint_set D(id.size());
    std::vector<std::tuple<double, int, int>> edge;
    for (int i = 0; i < (int)id.size(); ++i) {
      for (int j = 0; j < (int)id.size(); ++j) {
        edge.emplace_back(dist(id[i], id[j]), i, j);
      }
    }
    std::sort(edge.begin(), edge.end());
    for (auto [w, u, v] : edge) {
      if (D.merge(u, v)) {
        MST[S] += w;
      }
    }
  }
  
  std::vector<double> f(1 << n);
  f[0] = 1e18;
  for (int S = 1; S < (1 << n); ++S) {
    f[S] = 0;
    for (int T = S; T; T = (T - 1) & S) {
      f[S] = std::max(f[S], std::min(f[S ^ T], (sum[T] - MST[T]) / cnt[T]));
    }
  }
  std::cout << f.back() << "\n";
}
