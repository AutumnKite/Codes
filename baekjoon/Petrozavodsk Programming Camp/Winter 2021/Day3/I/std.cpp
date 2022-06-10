#include <bits/stdc++.h>

const int all = 10000000;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  std::vector<double> fac(all + 1);
  fac[0] = 0;
  for (int i = 1; i <= all; ++i) {
    fac[i] = fac[i - 1] + std::log(i);
  }

  std::vector<int> a;
  int x = 100;
  while (x <= all / 2) {
    a.push_back(x);
    x *= 1.01;
  }
  int n = a.size();
  std::vector<double> now(n, 1.0 / n);
  for (int T = 1; T <= 50; ++T) {
    std::vector<double> pr(n);
    
    auto calc = [&](int k) {
      for (int i = 0; i < n; ++i) {
        if (a[i] + k > all) {
          pr[i] = 1;
        } else {
          pr[i] = 1 - std::exp((fac[all - a[i]] - fac[all - a[i] - k]) -
                               (fac[all] - fac[all - k]));
        }
      }
      double res = 0;
      for (int i = 0; i < n; ++i) {
        res += pr[i] * now[i];
      }
      return res;
    };

    int l = 0, r = all;
    while (l + 1 < r) {
      int mid = (l + r) >> 1;
      if (calc(mid) >= 0.5) {
        r = mid;
      } else {
        l = mid;
      }
    }
    double p = calc(r);
    std::cout << "test " << l << std::endl;
    int x;
    std::cin >> x;
    if (x) {
      for (int i = 0; i < n; ++i) {
        now[i] = pr[i] * now[i] / p;
      }
    } else {
      for (int i = 0; i < n; ++i) {
        now[i] = (1 - pr[i]) * now[i] / (1 - p);
      }
    }
  }
  int id = std::max_element(now.begin(), now.end()) - now.begin();
  std::cout << "estimate " << a[id] << std::endl;
}
