#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  int max = *std::max_element(a.begin(), a.end()) + 1;
  std::vector<int> cnt(max);
  for (int i = 0; i < n; ++i) {
    ++cnt[a[i]];
  }
  std::vector<int> cntr(m), d(m);
  for (int i = 0; i < max; ++i) {
    cntr[i % m] += cnt[i];
  }
  int ans = 0;
  for (int i = 1; i + i < m; ++i) {
    int t = std::min(cntr[i], cntr[m - i]);
    ans += t;
    d[i] = d[m - i] = t;
  }
  d[0] = cntr[0] / 2 * 2;
  ans += cntr[0] / 2;
  if (m % 2 == 0) {
    d[m / 2] = cntr[m / 2] / 2 * 2;
    ans += cntr[m / 2] / 2;
  }

  for (int i = 0; i < max; ++i) {
    if (cnt[i] & 1 && d[i % m]) {
      --d[i % m];
      --cnt[i];
    }
  }
  for (int i = 0; i < max; ++i) {
    int t = std::min(cnt[i], d[i % m]);
    cnt[i] -= t, d[i % m] -= t;
  }
  for (int i = 0; i < max; ++i) {
    ans += cnt[i] / 2;
  }
  std::cout << ans << "\n";
}
