#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  std::vector<int> sta;
  std::vector<int> ls(n, -1), rs(n, -1);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    int lst = -1;
    while (!sta.empty() && a[sta.back()] < a[i]) {
      rs[sta.back()] = lst;
      lst = sta.back();
      sta.pop_back();
    }
    ls[i] = lst;
    sta.push_back(i);
  }
  int rt = -1;
  while (!sta.empty()) {
    rs[sta.back()] = rt;
    rt = sta.back();
    sta.pop_back();
  }

  std::vector<int> size(n);

  auto get_size = [&](auto &self, int u) -> int {
    if (u == -1) {
      return 0;
    }
    return size[u] = self(self, ls[u]) + self(self, rs[u]) + 1;
  };

  get_size(get_size, rt);

  std::vector<int> ans;

  auto get_ans = [&](auto &self, int u, int max) -> void {
    if (ls[u] != -1) {
      self(self, ls[u], std::max(max, a[u] - size[ls[u]]));
    }
    if (a[u] > max) {
      ans.push_back(u);
    }
    if (rs[u] != -1) {
      self(self, rs[u], std::max(max, a[u] - size[rs[u]]));
    }
  };

  get_ans(get_ans, rt, 0);
  std::cout << ans.size() << "\n";
  for (int x : ans) {
    std::cout << x + 1 << " ";
  }
  std::cout << "\n";
}
