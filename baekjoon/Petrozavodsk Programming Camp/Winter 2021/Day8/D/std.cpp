#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<long long> lst(40);
  std::vector<long long> f(40);
  for (int i = 0; i < n; ++i) {
    long long x;
    std::cin >> x;
    if (!x) {
      continue;
    }
    int h = std::__lg(x);
    long long s = 0;
    for (int j = 0; j < 40; ++j) {
      s = std::max(s, f[j] + (lst[j] & x));
    }
    f[h] = s;
    lst[h] = x;
  }
  std::cout << *std::max_element(f.begin(), f.end()) << "\n";
}
