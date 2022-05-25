#include <bits/stdc++.h>

std::vector<std::array<bool, 3>> solve1(std::vector<int> a) {
  int n = a.size();

  std::vector<std::pair<int, int>> seg;
  for (int i = 0, j = 0; i < n; i = j) {
    while (j < n && a[j] == a[i]) {
      ++j;
    }
    if (a[i] == 2) {
      seg.emplace_back(i, j);
    }
  }

  if ((int)seg.size() >= 3) {
    return {};
  }

  std::vector<std::array<bool, 3>> res(n);

  if (seg.empty()) {
    if (n < 3) {
      return {};
    }
    for (int i = 0; i < n; ++i) {
      res[i][std::min(i, 2)] = true;
    }
  } else if (seg.size() == 1) {
    for (int i = 0; i < n; ++i) {
      res[i][0] = true;
    }
    for (int i = seg[0].first; i < seg[0].second; ++i) {
      res[i][1] = true;
      res[i][2] = true;
    }
  } else {
    for (int i = 0; i < n; ++i) {
      res[i][0] = true;
    }
    for (int i = seg[0].first; i < seg[0].second; ++i) {
      res[i][1] = true;
    }
    for (int i = seg[1].first; i < seg[1].second; ++i) {
      res[i][2] = true;
    }
  }
  return res;
}

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

struct state {
  int x, y, d;

  state(int t_x, int t_y, int t_d) : x(t_x), y(t_y), d(t_d) {}

  state next() const {
    return state(x + dx[d], y + dy[d], d);
  }

  void change() {
    d = (d + 1) % 4;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> a(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char c;
      std::cin >> c;
      a[i][j] = c - '0';
    }
  }

  if (n == 1) {
    auto tmp = solve1(a[0]);
    if (tmp.empty()) {
      std::cout << "impossible\n";
      return 0;
    }
    for (int k = 0; k < 3; ++k) {
      for (int i = 0; i < m; ++i) {
        if (tmp[i][k]) {
          std::cout << char('A' + k);
        } else {
          std::cout << '.';
        }
      }
      std::cout << "\n\n";
    }
    return 0;
  }

  if (m == 1) {
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
      b[i] = a[i][0];
    }
    auto tmp = solve1(b);
    if (tmp.empty()) {
      std::cout << "impossible\n";
      return 0;
    }
    for (int k = 0; k < 3; ++k) {
      for (int i = 0; i < n; ++i) {
        if (tmp[i][k]) {
          std::cout << char('A' + k);
        } else {
          std::cout << '.';
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }
    return 0;
  }

  std::vector<std::vector<int>> col(n, std::vector<int>(m, 2));

  auto check = [&](state st) {
    return 0 <= st.x && st.x + 1 < n && 0 <= st.y && st.y < m &&
           col[st.x][st.y] == 2;
  };

  state p[2] = {state(0, 0, 0), state(0, m - 1, 1)};
  col[p[0].x][p[0].y] = 0;
  col[p[1].x][p[1].y] = 1;
  int which = 0, round = 0, rem = (n - 1) * m - 2;
  while (rem) {
    auto &st = p[which];
    while (check(st.next())) {
      st = st.next();
      col[st.x][st.y] = which;
      --rem;
    }
    st.change();
    which ^= 1;
    ++round;
    if (round == 2 || round == 5) {
      which ^= 1;
    }
  }

  std::vector<std::vector<std::array<bool, 3>>> ans(
      n, std::vector<std::array<bool, 3>>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ans[i][j][col[i][j]] = true;
      if (a[i][j] == 2) {
        for (int k = 0; k < 4; ++k) {
          int x = i + dx[k], y = j + dy[k];
          if (0 <= x && x < n && 0 <= y && y < m && col[x][y] != col[i][j]) {
            ans[i][j][col[x][y]] = true;
            break;
          }
        }
      }
    }
  }
  for (int k = 0; k < 3; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (ans[i][j][k]) {
          std::cout << char('A' + k);
        } else {
          std::cout << '.';
        }
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
}
