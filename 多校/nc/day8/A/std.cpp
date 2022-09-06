#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    --a[i];
  }
  std::vector<int> cnt(m);
  int tot = 0;
  long long ans = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n && tot < m) {
      tot += !cnt[a[j]];
      ++cnt[a[j]];
      ++j;
    }
    if (tot == m) {
      ans += n - j + 1;
    }
    --cnt[a[i]];
    tot -= !cnt[a[i]];
  }
  std::cout << ans << "\n";
}