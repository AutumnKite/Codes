#include <bits/stdc++.h>

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

std::vector<std::pair<int, int>> solve(std::vector<int> a) {
  int n = a.size();
  if (n == 4) {
    return {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
  }
  int pos = 0;
  while (a[pos] != 90 || a[(pos + 1) % n] != 270) {
    ++pos;
  }
  pos = (pos + n - 1) % n;
  std::vector<int> sub;
  for (int i = 0; i < n; ++i) {
    if (i != 1 && i != 2) {
      sub.push_back(a[(pos + i) % n]);
    }
  }
  auto res = solve(sub);
  for (auto &[x, y] : res) {
    x <<= 1;
    y <<= 1;
  }
  int d = (res[1].first + res[1].second > res[0].first + res[0].second) << 1 |
          (res[1].second != res[0].second);
  int x = res[0].first + dx[d], y = res[0].second + dy[d];
  d = (d + 1) % 4;
  res[1].first += dx[d];
  res[1].second += dy[d];
  res.insert(res.begin() + 1, {{x, y}, {x + dx[d], y + dy[d]}});
  std::vector<int> vx, vy;
  for (auto [x, y] : res) {
    vx.push_back(x);
    vy.push_back(y);
  }
  std::sort(vx.begin(), vx.end());
  vx.erase(std::unique(vx.begin(), vx.end()), vx.end());
  std::sort(vy.begin(), vy.end());
  vy.erase(std::unique(vy.begin(), vy.end()), vy.end());
  for (auto &[x, y] : res) {
    x = std::lower_bound(vx.begin(), vx.end(), x) - vx.begin();
    y = std::lower_bound(vy.begin(), vy.end(), y) - vy.begin();
  }
  std::rotate(res.begin(), res.begin() + n - pos, res.end());
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  int sum = 0;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    sum += a[i] == 90 ? 1 : -1;
  }
  if (sum != 4) {
    std::cout << -1 << "\n";
    return 0;
  }
  for (auto [x, y] : solve(a)) {
    std::cout << x << " " << y << "\n";
  }
}
