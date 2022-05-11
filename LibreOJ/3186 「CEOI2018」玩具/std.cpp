#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> d;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      d.push_back(i);
    }
  }

  std::vector<int> ans;

  auto dfs = [&](auto &self, auto lst, int n, int sum) -> void {
    ans.push_back(sum + n - 1);
    for (auto i = lst; i != d.end() && *i * *i <= n; ++i) {
      if (n % *i == 0) {
        self(self, i, n / *i, sum + *i - 1);
      }
    }
  };

  dfs(dfs, d.begin(), n, 0);
  std::sort(ans.begin(), ans.end());
  ans.erase(std::unique(ans.begin(), ans.end()), ans.end());
  std::cout << ans.size() << "\n";
  for (int v : ans) {
    std::cout << v << " ";
  }
  std::cout << "\n";
}
