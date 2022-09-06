#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;
  long long ans = 0;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    ans -= 1ll * a[i] * (i + 1) * (i + 1);
  }

  std::priority_queue<int> Q;
  for (int i = 0; i < k; ++i) {
    Q.push(a[i]);
  }
  for (int i = 0; i < n; ++i) {
    if (k + i < n) {
      Q.push(a[k + i]);
    }
    int c = Q.top();
    Q.pop();
    ans += 1ll * (k + i + 1) * (k + i + 1) * c;
  }
  std::cout << ans << "\n";
}
