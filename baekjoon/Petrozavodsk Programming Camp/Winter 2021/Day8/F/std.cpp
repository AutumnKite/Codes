#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> a(n), b(m, std::string(n, 'a'));
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    for (int j = 0; j < m; ++j) {
      b[j][i] = a[i][j];
    }
  }

  auto calc = [&](const auto &a, int lx, int rx, int ly, int ry) {
    int my = (ly + ry) / 2;
    std::vector<int> lenl(rx - lx), lenr(rx - lx);
    for (int i = lx; i < rx; ++i) {
      int l = 0, r = 0;
      while (my - l > ly && a[i][my - l - 1] == a[i][my]) {
        ++l;
      }
      while (my + r < ry && a[i][my + r] == a[i][my]) {
        ++r;
      }
      lenl[i - lx] = l, lenr[i - lx] = r;
    }
    std::vector<std::vector<int>> sl(rx - lx, std::vector<int>(rx - lx));
    std::vector<std::vector<int>> sr(rx - lx, std::vector<int>(rx - lx));
    std::vector<int> now(ry - ly);
    for (int i = lx; i < rx; ++i) {
      for (int j = ly; j < ry; ++j) {
        if (i == lx || a[i - 1][j] != a[i][j]) {
          now[j - ly] = 0;
        }
        ++now[j - ly];
      }
      std::vector<int> d(i - lx + 1);
      for (int j = 0; j < lenl[i - lx]; ++j) {
        ++d[now[my - j - 1 - ly] - 1];
      }
      for (int j = i - lx; j >= 1; --j) {
        d[j - 1] += d[j];
      }
      for (int j = 1; j <= i - lx; ++j) {
        if (lenl[i - j - lx] >= lenl[i - lx]) {
          sl[i - lx][i - j - lx] = d[j];
        }
      }
      std::fill(d.begin(), d.end(), 0);
      for (int j = 0; j < lenr[i - lx]; ++j) {
        ++d[now[my + j - ly] - 1];
      }
      for (int j = i - lx; j >= 1; --j) {
        d[j - 1] += d[j];
      }
      for (int j = 1; j <= i - lx; ++j) {
        if (lenr[i - j - lx] >= lenr[i - lx]) {
          sr[i - lx][i - j - lx] = d[j];
        }
      }
    }
    for (int i = rx - 1; i >= lx; --i) {
      for (int j = ly; j < ry; ++j) {
        if (i + 1 == rx || a[i + 1][j] != a[i][j]) {
          now[j - ly] = 0;
        }
        ++now[j - ly];
      }
      std::vector<int> d(rx - i);
      for (int j = 0; j < lenl[i - lx]; ++j) {
        ++d[now[my - j - 1 - ly] - 1];
      }
      for (int j = rx - i - 1; j >= 1; --j) {
        d[j - 1] += d[j];
      }
      for (int j = 1; j < rx - i; ++j) {
        if (lenl[i + j - lx] > lenl[i - lx]) {
          sl[i + j - lx][i - lx] = d[j];
        }
      }
      std::fill(d.begin(), d.end(), 0);
      for (int j = 0; j < lenr[i - lx]; ++j) {
        ++d[now[my + j - ly] - 1];
      }
      for (int j = rx - i - 1; j >= 1; --j) {
        d[j - 1] += d[j];
      }
      for (int j = 1; j < rx - i; ++j) {
        if (lenr[i + j - lx] > lenr[i - lx]) {
          sr[i + j - lx][i - lx] = d[j];
        }
      }
    }
    long long ans = 0;
    for (int i = 0; i < rx - lx; ++i) {
      for (int j = 0; j < i; ++j) {
        ans += 1ll * sl[i][j] * sr[i][j];
      }
    }
    return ans;
  };

  auto solve = [&](auto &self, int lx, int rx, int ly, int ry) -> long long {
    if (lx + 1 == rx || ly + 1 == ry) {
      return 0;
    }
    if (rx - lx < ry - ly) {
      int my = (ly + ry) / 2;
      long long ans = calc(a, lx, rx, ly, ry);
      ans += self(self, lx, rx, ly, my);
      ans += self(self, lx, rx, my, ry);
      return ans;
    } else {
      int mx = (lx + rx) / 2;
      long long ans = calc(b, ly, ry, lx, rx);
      ans += self(self, lx, mx, ly, ry);
      ans += self(self, mx, rx, ly, ry);
      return ans;
    }
  };

  std::cout << solve(solve, 0, n, 0, m) << "\n";
}
