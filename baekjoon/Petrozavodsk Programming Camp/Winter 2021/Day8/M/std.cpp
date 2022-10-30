#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n;
  std::cin >> n;
  int lst = 1, lst1 = 1;
  std::vector<long long> a(1, 1);
  for (int i = 2; 1ll * lst * i <= n; ++i) {
    if (std::__gcd(lst1, i) == 1) {
      a.push_back(1ll * lst * i);
      lst1 = lst, lst = i;
    }
  }
  int k = a.size();
  std::cout << k << "\n";
  for (auto x : a) {
    std::cout << x << " ";
  }
  std::cout << "\n";
}
