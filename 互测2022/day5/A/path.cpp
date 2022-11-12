#include "path.h"
#include <bits/stdc++.h>

int query(int x, int y, int z) {
  return ask(x + 1, y + 1, z + 1) - 1;
}

bool on_chain(int x, int y, int z) {
  return x == z || y == z || (x != y && query(x, y, z) == z);
}

std::mt19937 rnd(time(0));

int centroid(int sub, int n, int m) {
  if (sub == 1) {
    return query(0, 1, 2) + 1;
  }
  if (sub == 5) {
    int x = 0, y = 1;
    for (int i = 2; i < n; ++i) {
      if (on_chain(x, i, y)) {
        y = i;
      }
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::nth_element(p.begin(), p.begin() + n / 2, p.end(), [&](int i, int j) {
      return i != j && on_chain(y, j, i);
    });
    return p[n / 2] + 1;
  }

  auto check_root = [&](int rt) {
    int now = -1, d = 0;
    for (int i = 0; i < n; ++i) {
      if (i != rt) {
        if (d == 0 || now == -1) {
          now = i;
          d = 1;
          continue;
        }
        if (on_chain(now, i, rt)) {
          --d;
        } else {
          ++d;
        }
      }
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (i != rt && !on_chain(now, i, rt)) {
        ++cnt;
      }
    }
    return cnt <= n / 2;
  };

  for (;;) {
    int x, y;
    do {
      x = rnd() % n;
      y = rnd() % n;
    } while (x == y);
    std::vector<int> type(n, -1);
    for (int i = 0; i < n; ++i) {
      if (on_chain(x, y, i)) {
        type[i] = -2;
      }
    }
    int res;
    for (;;) {
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        cnt += type[i] == -2;
      }
      if (cnt == 1) {
        res = std::find(type.begin(), type.end(), -2) - type.begin();
        break;
      }
      int z;
      do {
        z = rnd() % n;
      } while (type[z] >= 0);
      int mid = z;
      if (type[z] != -2) {
        for (int i = 0; i < n; ++i) {
          if (type[i] == -2 && on_chain(x, z, i) && on_chain(y, z, i)) {
            mid = i;
            break;
          }
        }
      }
      std::vector<bool> L(n), R(n);
      int cntL = 0, cntR = 0, cntM = 0;
      for (int i = 0; i < n; ++i) {
        L[i] = type[i] == 0 || y == mid || (type[i] < 0 && on_chain(y, i, mid));
        R[i] = type[i] == 1 || x == mid || (type[i] < 0 && on_chain(x, i, mid));
        cntL += L[i] && !R[i];
        cntR += R[i] && !L[i];
        cntM += L[i] && R[i];
      }
      --cntM;
      if (cntL > n / 2) {
        for (int i = 0; i < n; ++i) {
          if (type[i] < 0 && R[i]) {
            type[i] = 1;
          }
        }
      } else if (cntR > n / 2) {
        for (int i = 0; i < n; ++i) {
          if (type[i] < 0 && L[i]) {
            type[i] = 0;
          }
        }
      } else if (cntM > n / 2) {
        res = mid;
        break;
      } else {
        return mid + 1;
      }
    }
    if (check_root(res)) {
      return res + 1;
    }
  }
}

#ifdef LOCAL
#include "grader.cpp"
#endif
