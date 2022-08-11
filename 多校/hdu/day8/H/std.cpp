#include <bits/stdc++.h>

int main() {
  // int stack_limit(512 << 20);
  // __asm__("movq %0, %%rsp\n"::"r"((char*)malloc(stack_limit) + stack_limit));

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> E(n);
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      E[u].push_back(v);
      E[v].push_back(u);
    }

    std::vector<std::array<int, 3>> f(n);

    std::function<void(int, int)> dfs = [&](int u, int fa) {
      for (int v : E[u]) {
        if (v != fa) {
          dfs(v, u);
          f[u][0] += std::max(f[v][0], std::max(f[v][1], f[v][2]));
          f[u][1] += f[v][0];
          f[u][2] = std::max(f[u][2], f[v][1] - f[v][0]);
        }
      }
      f[u][1] += 1;
      f[u][2] += f[u][1];
    };

    dfs(0, -1);
    std::cout << std::max(f[0][0], std::max(f[0][1], f[0][2])) << "\n";
  }

  exit(0);
}
