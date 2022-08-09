#include <bits/stdc++.h>

std::vector<int> build_fail(const std::string &s) {
  int n = s.size();
  std::vector<int> fail(n + 1, -1);
  fail[1] = 0;
  for (int i = 1, j = 0; i < n; ++i) {
    while (j && s[i] != s[j]) {
      j = fail[j];
    }
    if (s[i] == s[j]) {
      ++j;
    }
    fail[i + 1] = j;
  }
  return fail;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  std::string s;
  std::cin >> s;
  std::vector<int> cost(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> cost[i];
  }

  std::vector<std::vector<int>> cnt(n, std::vector<int>(n + 1, -1));
  for (int l = 0; l < n; ++l) {
    auto fail = build_fail(s.substr(l));
    std::vector<std::vector<int>> E(n - l + 1);
    for (int i = 1; i <= n - l; ++i) {
      E[fail[i]].push_back(i);
    }

    auto dfs = [&](auto &self, int u, std::vector<int> &pos) -> void {
      pos.push_back(l + u);
      for (int v : E[u]) {
        self(self, v, pos);
      }
    };

    for (int i = 1; i <= n - l; ++i) {
      if (cnt[l][i] == -1) {
        std::vector<int> pos;
        dfs(dfs, i, pos);
        for (int x : pos) {
          cnt[x - i][i] = pos.size();
        }
      }
    }
  }

  while (q--) {
    int l, r;
    std::cin >> l >> r;
    --l;
    auto fail = build_fail(s.substr(l, r - l));
    long long ans = 0;
    for (int x = r - l; x; x = fail[x]) {
      ans += cost[cnt[l][x]];
    }
    std::cout << ans << "\n";
  }
}
