#include "path.h"
#include <bits/stdc++.h>

int query(int x, int y, int z) {
  if (z == x) {
    return -3;
  }
  if (z == y) {
    return -2;
  }
  int t = ask(x + 1, y + 1, z + 1) - 1;
  if (t == x) {
    return 0;
  } else if (t == y) {
    return 1;
  } else if (t == z) {
    return 2;
  } else {
    return -1;
  }
}

const int LIM[] = {1, 1000, 100, 100, 5, 40, 26, 16};

std::mt19937 rnd(time(0));

int centroid(int sub, int n, int m) {
  --sub;
  std::vector<int> vis(n, -1);
  std::vector<bool> path(n, true);
  int x = rnd() % n;
  int qcnt = 0;

  auto check = [&]() {
    int now = qcnt;
    for (int i = 0; i < n; ++i) {
      if (vis[i] < 0) {
        ++now;
      }
    }
    // return now <= LIM[sub] * n;
    return true;
  };

  while (check()) {
    std::vector<int> p;
    for (int i = 0; i < n; ++i) {
      if (path[i]) {
        p.push_back(i);
      }
    }
    if (p.size() == 1) {
      return p[0] + 1;
    }
    int y;
    do {
      y = p[rnd() % p.size()];
    } while (x == y);

    std::vector<int> s(n);
    int cnt[3] = {};
    for (int i = 0; i < n; ++i) {
      if (vis[i] < 0) {
        s[i] = query(x, y, i);
        qcnt += x != i && y != i;
      } else {
        s[i] = vis[i];
      }
      ++cnt[(s[i] + 3) % 3];
    }
    int which;
    if (cnt[0] * 2 > n) {
      which = 0;
    } else if (cnt[1] * 2 > n) {
      which = 1;
    } else {
      which = 2;
    }

    if (which == 0) {
      for (int i = 0; i < n; ++i) {
        if (i != x && s[i] != 0) {
          vis[i] = 0;
          path[i] = false;
        }
      }
    } else if (which == 1) {
      for (int i = 0; i < n; ++i) {
        if (i != y && s[i] != 1) {
          vis[i] = 0;
          path[i] = false;
        } else {
          if (sub == 2 || sub == 4) {
            continue;
          }
          if (vis[i] == -1) {
            path[i] = true;
          } else {
            vis[i] = -2;
          }
        }
      }
      x = y;
    } else {
      for (int i = 0; i < n; ++i) {
        if (i != x && i != y && s[i] != 2) {
          if (s[i] == 0) {
            vis[i] = 0;
          } else if (s[i] == 1) {
            vis[i] = 1;
          }
          path[i] = false;
        }
      }
      std::swap(x, y);
      for (int i = 0; i < n; ++i) {
        if (vis[i] >= 0) {
          vis[i] ^= 1;
        }
      }
      vis[y] = 1;
      path[y] = false;
    }
  }
  return x;
}

#ifdef LOCAL
#include "grader.cpp"
#endif
