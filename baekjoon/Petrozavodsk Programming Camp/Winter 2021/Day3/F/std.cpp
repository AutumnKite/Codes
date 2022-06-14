#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i].first;
    a[i].second = i;
  }

  if (k == 0 || k % m != 0) {
    std::cout << "impossible\n";
    return 0;
  }
  k /= m;
  std::sort(a.begin(), a.end());
  std::reverse(a.begin(), a.end());

  int l = k - 1, r = k;
  std::vector<int> ans;
  int now = 0, cnt = 0;
  while (cnt < n) {
    if (l >= 0 && now * m <= a[l].first * cnt) {
      ans.push_back(a[l--].second);
      ++now, ++cnt;
    } else if (r < n && now * m > a[r].first * cnt) {
      ans.push_back(a[r++].second);
      ++cnt;
    } else {
      std::cout << "impossible\n";
      return 0;
    }
  }
  for (int x : ans) {
    std::cout << x + 1 << " ";
  }
  std::cout << "\n";
}
