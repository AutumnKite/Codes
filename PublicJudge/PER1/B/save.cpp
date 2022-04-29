#include <bits/stdc++.h>
#include "save.h"

void read_array(int subtask_id, const std::vector<int> &a) {
  int n = a.size();
  std::vector<std::array<int, 2>> son(n, {-1, -1});
  std::vector<int> sta;
  for (int i = 0; i < n; ++i) {
    int lst = -1;
    while (!sta.empty() && a[sta.back()] < a[i]) {
      son[sta.back()][1] = lst;
      lst = sta.back();
      sta.pop_back();
    }
    son[i][0] = lst;
    sta.push_back(i);
  }
  int lst = -1;
  while (!sta.empty()) {
    son[sta.back()][1] = lst;
    lst = sta.back();
    sta.pop_back();
  }

  std::string res;

  auto dfs = [&](auto &self, int u) -> void {
    res += '0';
    if (son[u][0] != -1) {
      self(self, son[u][0]);
    }
    res += '1';
    if (son[u][1] != -1) {
      self(self, son[u][1]);
    }
  };

  dfs(dfs, lst);
  save_to_floppy(res);
}
