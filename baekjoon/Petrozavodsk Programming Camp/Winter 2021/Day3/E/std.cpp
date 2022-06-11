#include <bits/stdc++.h>

struct point {
  int x, y, c;

  point(int t_x, int t_y, int t_c) : x(t_x), y(t_y), c(t_c) {}

  bool operator<(const point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<point> a;
  for (int i = 0; i < n; ++i) {
    int x, y;
    char c;
    std::cin >> x >> y >> c;
    x *= 2;
    a.emplace_back(x + y, y - x, c == 'N' ? 0 : (c == 'P' ? 1 : -1));
  }
  std::sort(a.begin(), a.end());
  std::reverse(a.begin(), a.end());

  std::vector<int> col(n, -1);
  std::priority_queue<std::pair<int, int>> S;
  for (int i = 0; i < n; ++i) {
    S.emplace(a[i].y, i);
    if (a[i].c == 0) {
      while (!S.empty() && S.top().first >= a[i].y) {
        int j = S.top().second;
        S.pop();
        if (a[j].c == 1) {
          std::cout << "impossible\n";
          return 0;
        }
        col[j] = 0;
      }
    }
  }
  while (!S.empty()) {
    S.pop();
  }
  std::priority_queue<std::pair<int, int>> T;
  for (int i = 0; i < n; ++i) {
    if (col[i] == -1) {
      col[i] = 0;
      S.emplace(a[i].y, i);
      if (a[i].c == 1 && (T.empty() || T.top().first < a[i].y)) {
        int j = S.top().second;
        S.pop();
        col[j] = 1;
        T.emplace(a[j].y, j);
      }
    }
  }
  std::cout << T.size() << "\n";
}
