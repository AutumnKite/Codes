#include <bits/stdc++.h>

int main() {
  int T;
  std::cin >> T;
  while (T--) {
    int p, q, a;
    std::cin >> p >> q >> a;
    long long t = 1ll * p * q - 1;
    std::vector<long long> ans;
    for (int i = 2; 1ll * i * i <= t; ++i) {
      if (t % i == 0) {
        while (t % i == 0) {
          t /= i;
        }
        if (p < i && q < i && a < i) {
          ans.push_back(1ll * a * q % i);
        }
      }
    }
    if (t > 1 && p < t && q < t && a < t) {
      ans.push_back(1ll * a * q % t);
    }
    std::sort(ans.begin(), ans.end());
    ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
    if (ans.size() == 1) {
      std::cout << ans[0] << "\n";
    } else {
      std::cout << "shuanQ\n";
    }
  }
}
