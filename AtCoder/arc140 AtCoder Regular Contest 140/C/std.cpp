#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, x;
  std::cin >> n >> x;
  --x;
  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  id.erase(id.begin() + x);

  auto l = id.begin(), r = id.end();
  int which = x < n / 2;
  std::vector<int> ans;
  while (l != r) {
    if (which) {
      ans.push_back(*--r);
    } else {
      ans.push_back(*l++);
    }
    which ^= 1;
  }
  ans.push_back(x);
  std::reverse(ans.begin(), ans.end());
  for (int x : ans) {
    std::cout << x + 1 << " ";
  }
  std::cout << "\n";
}
