#include <bits/stdc++.h>

constexpr int INF = std::numeric_limits<int>::max() / 2;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, x;
  std::cin >> n >> x;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  std::vector<int> f(n);
  std::vector<int> sta(n + 1, INF);
  sta[0] = 0;
  for (int i = 0; i < n; ++i) {
    int p = std::lower_bound(sta.begin(), sta.end(), a[i]) - sta.begin();
    f[i] = p;
    sta[p] = a[i];
  }
  int ans = *std::max_element(f.begin(), f.end());
  sta.assign(n + 1, -INF);
  sta[0] = INF;
  for (int i = n - 1; i >= 0; --i) {
    int p = sta.rend() - std::upper_bound(sta.rbegin(), sta.rend(), a[i] - x);
    ans = std::max(ans, f[i] + p - 1);
    p = sta.rend() - std::upper_bound(sta.rbegin(), sta.rend(), a[i]);
    sta[p] = a[i];
  }
  std::cout << ans << "\n";
}
