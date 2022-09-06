#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a(n);
    std::vector<std::pair<int, int>> pos(n * (n + 1) / 2);
    for (int i = 0; i < n; ++i) {
      a[i].resize(i + 1);
      for (int j = 0; j <= i; ++j) {
        std::cin >> a[i][j];
        --a[i][j];
        pos[a[i][j]] = std::make_pair(i, j);
      }
    }

    std::vector<std::pair<int, int>> ans;

    auto swap = [&](std::pair<int, int> p, std::pair<int, int> q) {
      std::swap(a[p.first][p.second], a[q.first][q.second]);
      std::swap(pos[a[p.first][p.second]], pos[a[q.first][q.second]]);
    };

    auto rotate = [&](int x, int y) {
      std::vector<std::pair<int, int>> p;
      if (y & 1) {
        p.emplace_back(x, y / 2);
        p.emplace_back(x, y / 2 + 1);
        p.emplace_back(x + 1, y / 2 + 1);
      } else {
        p.emplace_back(x, y / 2);
        p.emplace_back(x + 1, y / 2 + 1);
        p.emplace_back(x + 1, y / 2);
      }
      swap(p[1], p[2]);
      swap(p[0], p[1]);
      ans.emplace_back(x, y);
    };

    bool ok = true;
    int idx = n * (n + 1) / 2;
    for (int i = n - 1; i > 0; --i) {
      idx -= i + 1;
      for (int j = i; j >= 0; --j) {
        int v = idx + j - (j == 1) + (j == 0);
        if (pos[v] == std::make_pair(i, j)) {
          rotate(pos[v].first - 1, (pos[v].second - 1) * 2);
        }
        while (pos[v].first > i - 1) {
          rotate(pos[v].first - 1, pos[v].second * 2);
        }
        while (pos[v].first < i - 1) {
          rotate(pos[v].first, pos[v].second * 2);
        }
        while (pos[v].second > std::max(j - 1, 0)) {
          rotate(pos[v].first - 1, (pos[v].second - 1) * 2);
        }
        while (pos[v].second < std::max(j - 1, 0)) {
          rotate(pos[v].first - 1, pos[v].second * 2);
          rotate(pos[v].first, pos[v].second * 2);
        }
        if (j != 1 || a[i][j] != idx + 1) {
          rotate(pos[v].first, pos[v].second * 2);
        } else if (i > 1) {
          rotate(i - 1, 1);
          rotate(i - 1, 1);
        } else {
          ok = false;
          break;
        }
      }
    }
    if (!ok) {
      std::cout << "No\n";
      continue;
    }
    std::cout << "Yes\n";
    std::cout << ans.size() << "\n";
    for (auto p : ans) {
      std::cout << p.first + 1 << " " << p.second + 1 << "\n";
    }
  }
}
