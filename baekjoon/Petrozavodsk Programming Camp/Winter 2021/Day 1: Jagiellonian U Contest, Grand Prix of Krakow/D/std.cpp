#include <bits/stdc++.h>

constexpr long long INF = std::numeric_limits<long long>::max();

struct state {
  long long v;
  int pre, x, y;

  state() : v(INF), pre(), x(), y() {}

  bool operator<(const state &rhs) const {
    return v < rhs.v;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> E(n, std::vector<int>(n));
    std::vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        std::cin >> E[i][j];
        deg[i] += E[i][j] > 0;
      }
    }

    if (n == 2) {
      std::cout << "NO\n";
      continue;
    }

    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin(), id.end(), [&](int x, int y) {
      return deg[x] < deg[y];
    });

    std::vector<std::vector<int>> a;
    std::vector<int> now;
    std::vector<int> bel(n);
    int cnt = 0, sum = 0;
    for (int i : id) {
      now.push_back(i);
      bel[i] = a.size();
      ++cnt, sum += deg[i];
      if (sum == cnt * (cnt - 1) / 2) {
        a.push_back(now);
        now.clear();
      }
    }

    std::vector<state> f(a.size());
    f[0].v = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
      std::pair<long long, int> min(INF, 0);
      for (int j = i - 1; j >= 0; --j) {
        min = std::min(min, std::make_pair(f[j].v, j));
        for (int x : a[i]) {
          for (int y : a[j]) {
            state tmp;
            tmp.v = min.first + E[x][y];
            tmp.pre = min.second;
            tmp.x = x;
            tmp.y = y;
            f[i] = std::min(f[i], tmp);
          }
        }
      }
    }

    std::vector<std::pair<int, int>> ans;
    int k = (int)a.size() - 1;
    while (k > 0) {
      ans.emplace_back(f[k].x, f[k].y);
      k = f[k].pre;
    }

    std::cout << "YES\n";
    std::cout << ans.size() << " " << f.back().v << "\n";
    for (auto [x, y] : ans) {
      std::cout << x + 1 << " " << y + 1 << "\n";
    }
  }
}
