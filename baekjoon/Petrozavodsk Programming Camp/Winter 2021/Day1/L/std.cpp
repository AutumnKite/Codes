#include <bits/stdc++.h>

const int LIM = 10000;

const char name[] = "WSEN";
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int get_dir(char c) {
  return std::find(name, name + 4, c) - name;
}

int get_dir(int dx, int dy) {
  for (int i = 0; i < 4; ++i) {
    if (::dx[i] == dx && ::dy[i] == dy) {
      return i;
    }
  }
  return 4;
}

auto solve(int x0, int y0, std::string s) {
  std::vector<std::pair<int, int>> a;
  for (char c : s) {
    a.emplace_back(x0, y0);
    int d = get_dir(c);
    x0 += dx[d];
    y0 += dy[d];
  }

  std::vector<int> oper;
  while (!a.empty()) {
    int minx = LIM, miny = LIM;
    int maxx = -LIM, maxy = -LIM;
    for (auto [x, y] : a) {
      minx = std::min(minx, x);
      maxx = std::max(maxx, x);
      miny = std::min(miny, y);
      maxy = std::max(maxy, y);
    }

    auto it = a.begin();

    auto next = [&](decltype(it) x) {
      auto nx = std::next(x);
      if (nx == a.end()) {
        return a.begin();
      } else {
        return nx;
      }
    };

    bool ok = true;
    while (it != a.end()) {
      auto &[Ax, Ay] = *it;
      auto &[Bx, By] = *next(it);
      auto &[Cx, Cy] = *next(next(it));
      int d0 = get_dir(Bx - Ax, By - Ay);
      int d1 = get_dir(Cx - Bx, Cy - By);
      int tp = d0 ^ d1;
      if (tp == 2) {
        x0 = Ax, y0 = Ay;
        ok = false;
        oper.push_back(d0);
        for (int i = 0; i < 2; ++i) {
          auto tmp = next(it);
          if (tmp <= it) {
            --it;
          }
          a.erase(tmp);
        }
      } else {
        if (tp) {
          if (((d0 == 0 && Bx == minx) || (d0 == 2 && Bx == maxx)) &&
              (Ax || Cy)) {
            ok = false;
            oper.push_back(-2);
            Bx = Ax, By = Cy;
          } else if (((d0 == 1 && By == miny) || (d0 == 3 && By == maxy)) &&
                     (Cx || Ay)) {
            ok = false;
            oper.push_back(-2);
            Bx = Cx, By = Ay;
          }
        }
        oper.push_back(-1);
        ++it;
      }
    }
    if (ok) {
      break;
    }
  }

  if (a.empty()) {
    if (y0 == 0 && x0 < 0) {
      oper.push_back(5);
      oper.push_back(-1);
      oper.push_back(3);
      --y0;
    }
    while (x0 > 1) {
      oper.push_back(4);
      oper.push_back(-1);
      oper.push_back(2);
      --x0;
    }
    while (x0 < 1) {
      oper.push_back(6);
      oper.push_back(-1);
      oper.push_back(0);
      ++x0;
    }
    while (y0 > 0) {
      oper.push_back(5);
      oper.push_back(-1);
      oper.push_back(3);
      --y0;
    }
    while (y0 < 0) {
      oper.push_back(7);
      oper.push_back(-1);
      oper.push_back(1);
      ++y0;
    }
  } else {
    auto it = a.begin();
    while (it != a.end() && *it != std::make_pair(1, 0)) {
      oper.push_back(-1);
      ++it;
    }
    std::rotate(a.begin(), it, a.end());
  }
  return std::make_pair(a, oper);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int x0, y0;
    std::cin >> x0 >> y0;
    int n, m;
    std::cin >> n >> m;
    std::string s, t;
    std::cin >> s >> t;

    std::reverse(t.begin(), t.end());
    for (char &c : t) {
      c = name[get_dir(c) ^ 2];
    }

    auto [A, operA] = solve(x0, y0, s);
    auto [B, operB] = solve(x0, y0, t);

    if (!B.empty()) {
      std::reverse(B.begin() + 1, B.end());
    }

    if (A != B) {
      std::cout << "NO\n";
      continue;
    }

    for (std::size_t i = 2; i < A.size(); ++i) {
      operA.push_back(-1);
    }
    std::reverse(operB.begin(), operB.end());
    for (auto x : operB) {
      if (x == -1) {
        operA.push_back(-1);
      } else if (x == -2) {
        operA.push_back(-2);
      } else if (x < 4) {
        operA.push_back(-1);
        operA.push_back(-1);
        operA.push_back(x + 4);
      } else {
        operA.push_back(x - 4);
      }
    }
    operA.push_back(-1);
    operA.push_back(-1);

    std::cout << "YES\n";
    for (auto x : operA) {
      if (x == -1) {
        std::cout << '-';
      } else if (x == -2) {
        std::cout << 'C';
      } else if (x < 4) {
        std::cout << 'R';
      } else {
        std::cout << name[x - 4];
      }
    }
    std::cout << "\n";
  }
}
