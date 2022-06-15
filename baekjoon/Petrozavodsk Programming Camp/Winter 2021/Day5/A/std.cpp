#include <bits/stdc++.h>

int n, m;
int a[11][1000];
bool vis[11], S[1000], ans[1000];

void dfs(int k) {
  if (k == m) {
    return;
  }
  for (int i = 0; i < m; ++i) {
    if (!vis[i]) {
      int j = 0;
      while (S[a[i][j]]) {
        ++j;
      }
      vis[i] = true;
      S[a[i][j]] = true;
      ans[a[i][j]] = true;
      dfs(k + 1);
      vis[i] = false;
      S[a[i][j]] = false;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> a[i][j];
      --a[i][j];
    }
  }

  dfs(0);
  std::cout << std::accumulate(ans, ans + n, 0) << "\n";
  for (int i = 0; i < n; ++i) {
    if (ans[i]) {
      std::cout << i + 1 << " ";
    }
  }
  std::cout << "\n";
}
