#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    --l;
    int now = 1;
    std::priority_queue<int, std::vector<int>, std::greater<int>> Q;
    long long ans = 0;
    for (int i = l; i < r; ++i) {
      if (now > 0) {
        ans += a[i];
        Q.push(a[i]);
        --now;
      } else {
        ++now;
        if (!Q.empty() && Q.top() < a[i]) {
          ans -= Q.top();
          Q.pop();
          ans += a[i];
          Q.push(a[i]);
        }
      }
    }
    std::cout << ans << "\n";
  }
}
