#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
  int test, lim, cnt;
  std::cin >> test >> lim >> cnt;

  std::string name = "friends" + std::to_string(test);
  freopen((name + ".in").c_str(), "r", stdin);
  freopen((name + ".out").c_str(), "w", stdout);

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<bool>> E(n, std::vector<bool>(n));
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    E[u][v] = E[v][u] = true;
  }

  auto G(E);

  int rem = m;

  auto find = [&]() {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::vector<int> res;
    int max = 0;
    for (int i = 1; i <= lim; ++i) {
      std::shuffle(p.begin(), p.end(), rnd);
      std::vector<bool> vis(n);
      std::vector<int> now;
      int s = 0;
      int id = 0;
      for (int u : p) {
        ++id;
        if (id > cnt) {
          break;
        }
        bool flag = true;
        for (int v : now) {
          if (!E[u][v]) {
            flag = false;
            break;
          }
        }
        if (!flag) {
          continue;
        }
        int t = 0;
        for (int v : now) {
          t += G[u][v];
        }
        if (now.empty() || t) {
          s += t;
          now.push_back(u);
        }
      }
      if (s > max) {
        max = s;
        res = std::move(now);
      }
    }
    rem -= max;
    for (int u : res) {
      for (int v : res) {
        G[u][v] = false;
      }
    }
    return res;
  };

  std::vector<std::vector<int>> ans;
  while (rem) {
    auto tmp = find();
    if (!tmp.empty()) {
      ans.push_back(tmp);
    }
    std::cerr << rem << "\n";
  }

  std::cout << ans.size() << "\n";
  for (auto p : ans) {
    std::cout << p.size();
    for (int x : p) {
      std::cout << " " << x + 1;
    }
    std::cout << "\n";
  }
}
