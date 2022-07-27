#include <bits/stdc++.h>

struct point {
  int x, y, z;

  point() : x(), y(), z() {}

  point(int t_x, int t_y, int t_z) : x(t_x), y(t_y), z(t_z) {}

  point operator+(const point &rhs) const {
    return point(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  point operator-(const point &rhs) const {
    return point(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  bool operator==(const point &rhs) const {
    return x == rhs.x && y == rhs.y && z == rhs.z;
  }
};

int dot(point a, point b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

point cross(point a, point b) {
  return point(a.y * b.z - b.y * a.z, a.z * b.x - a.x * b.z,
               a.x * b.y - a.y * b.x);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::pair<point, point>> seg;
    std::vector<point> p;
    for (int i = 0; i < n; ++i) {
      int sx, sy, sz, tx, ty, tz;
      std::cin >> sx >> sy >> sz >> tx >> ty >> tz;
      seg.emplace_back(point(sx, sy, sz), point(tx, ty, tz));
      p.emplace_back(sx, sy, sz);
      p.emplace_back(tx, ty, tz);
    }
    int ans = -1;
    for (int i = 0; i < 2 * n; ++i) {
      for (int j = i; j < 2 * n; ++j) { 
        for (int k = j; k < 2 * n; ++k) {
          point d = cross(p[j] - p[i], p[k] - p[i]);
          if (d == point(0, 0, 0)) {
            continue;
          }
          int cnt = 0;
          for (int t = 0; t < n; ++t) {
            int u = dot(seg[t].first - p[i], d);
            int v = dot(seg[t].second - p[i], d);
            if ((u <= 0 && v >= 0) || (u >= 0 && v <= 0)) {
              ++cnt;
            }
          }
          ans = std::max(ans, cnt);
        }
      }
    }
    if (ans == -1) {
      ans = n;
    }
    std::cout << ans << "\n";
  }
}
