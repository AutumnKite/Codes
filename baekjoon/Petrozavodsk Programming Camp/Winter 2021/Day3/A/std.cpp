#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;
  std::vector<int> a(k), b(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < k; ++i) {
    std::cin >> b[i];
  }

  std::vector<int> s(k + 1);
  for (int i = 0; i < k; ++i) {
    s[i + 1] = s[i] + b[i] - a[i];
  }
  int x = -*std::min_element(s.begin(), s.end());
  for (int i = 0; i <= k; ++i) {
    s[i] += x;
  }
  int tot = std::accumulate(s.begin(), s.end(), 0);
  int p = 0;

  auto check = [&](int p) {
    if (!s[p]) {
      return false;
    }
    if (p == 0) {
      return a[p] >= 3;
    } else if (p == k) {
      return a[p - 1] <= n - 2;
    } else {
      return a[p] - a[p - 1] >= 4;
    }
  };

  auto work = [&](int p) {
    if (p == 0) {
      --a[p];
    } else if (p == k) {
      ++a[p - 1];
    } else {
      ++a[p - 1];
      --a[p];
    }
    --s[p];
  };

  for (int i = 0; i < tot; ++i) {
    while (p <= k && !check(p)) {
      ++p;
    }
    if (p > k) {
      std::cout << "impossible\n";
      return 0;
    }
    work(p);
    p = std::max(p - 1, 0);
  }
  std::cout << tot << "\n";
}
