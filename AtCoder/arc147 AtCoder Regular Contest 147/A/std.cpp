#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::deque<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::sort(a.begin(), a.end());
  int cnt = 0;
  while (a.size() > 1) {
    int v = a.back() % a.front();
    a.pop_back();
    if (v) {
      a.push_front(v);
    }
    ++cnt;
  }
  std::cout << cnt << "\n";
}
