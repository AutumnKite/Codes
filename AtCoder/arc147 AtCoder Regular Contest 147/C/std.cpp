#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> l(n), r(n);
  std::vector<int> val;
  for (int i = 0; i < n; ++i) {
    std::cin >> l[i] >> r[i];
    val.push_back(l[i]);
    val.push_back(r[i]);
  }
  std::sort(val.begin(), val.end());
  val.erase(std::unique(val.begin(), val.end()), val.end());
  int m = val.size();
  std::vector<int> a(m), b(m);
  std::vector<long long> ai(m), bi(m);
  std::vector<long long> aii(m), bii(m);
  for (int i = 0; i < n; ++i) {
    l[i] = std::lower_bound(val.begin(), val.end(), l[i]) - val.begin();
    r[i] = std::lower_bound(val.begin(), val.end(), r[i]) - val.begin();
    ++a[r[i]];
    ++b[l[i]];
  }
  for (int i = 0; i < m; ++i) {
    int c = a[i];
    ai[i] = 1ll * c * val[i];
    if (i) {
      a[i] += a[i - 1];
      ai[i] += ai[i - 1];
      aii[i] = aii[i - 1] + (1ll * a[i] * val[i] - ai[i]) * c;
    }
  }
  for (int i = m - 1; i >= 0; --i) {
    int c = b[i];
    bi[i] = 1ll * c * val[i];
    if (i + 1 < m) {
      b[i] += b[i + 1];
      bi[i] += bi[i + 1];
      bii[i] = bii[i + 1] + (bi[i] - 1ll * b[i] * val[i]) * c;
    }
  }
  long long ans = 1e18;
  for (int i = 0; i < m; ++i) {
    int c = n - a[i] - b[i];
    ans = std::min(ans, aii[i] + bii[i] + 1ll * c * val[i] * (a[i] - b[i]) -
                        ai[i] * (n - a[i]) + bi[i] * (n - b[i]));
  }
  std::cout << ans << "\n";
}
