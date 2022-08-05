#include <bits/stdc++.h>

std::vector<int> manacher(const std::string &s) {
  int n = s.size();
  std::vector<int> h(n);
  for (int i = 0, m = 0, r = 0; i < n; ++i) {
    if (i < r) {
      h[i] = std::min(h[2 * m - i], r - i);
    } else {
      h[i] = 0;
    }
    while (i - h[i] >= 0 && i + h[i] < n && s[i - h[i]] == s[i + h[i]]) {
      ++h[i];
    }
    if (i + h[i] > r) {
      m = i, r = i + h[i];
    }
  }
  return h;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::string t = "#";
  for (char c : s) {
    t += c;
    t += '#';
  }
  n = 2 * n + 1;
  auto h = manacher(t);
  std::vector<std::array<int, 3>> pre(n + 1);
  for (int i = 0; i < n; ++i) {
    pre[i + 1] = pre[i];
    if (t[i] == 'k') {
      ++pre[i + 1][0];
    }
    if (t[i] == 'f') {
      ++pre[i + 1][1];
    }
    if (t[i] == 'c') {
      ++pre[i + 1][2];
    }
  }
  long long ans[3] = {};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 3; ++j) {
      ans[j] += pre[i + h[i]][j] - pre[i][j];
    }
  }
  std::cout << ans[0] << " " << ans[1] << " " << ans[2] << "\n";
}
