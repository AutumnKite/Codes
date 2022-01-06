#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  long long ans = 0;
  for (int q = 1; q <= n; ++q) {
    int v, l, r, k;
    std::cin >> v >> l >> r >> k;
    v = (v + ans) % (n + 1);
    l = (l + ans) % q;
    r = (r + ans) % q;
    k = (k + ans) % (n + 1);
    if (l > r) {
      std::swap(l, r);
    }
    ++r;
    
  }
}
