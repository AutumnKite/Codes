#include <bits/stdc++.h>

const char name[] = "nsew";

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;
    if (c == '?') {
      a[i] = -1;
    } else {
      int x;
      std::cin >> x;
      a[i] = (std::find(name, name + 4, c) - name) * 7 + x - 1;
    }
  }
  std::vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    char c;
    std::cin >> c;
    if (c == '?') {
      b[i] = -1;
    } else {
      int x;
      std::cin >> x;
      b[i] = (std::find(name, name + 4, c) - name) * 7 + x - 1;
    }
  }

  const int C = 28;
  std::vector<std::bitset<400000>> mask(C);
  for (int i = 0; i < C; ++i) {
    mask[i].set();
  }
  for (int i = 0; i < m; ++i) {
    if (b[i] != -1) {
      mask[b[i]].reset(i);
    } else {
      for (int j = 0; j < C; ++j) {
        mask[j].reset(i);
      }
    }
  }
  std::bitset<400000> S;
  S.set();
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    S <<= 1;
    if (a[i] != -1) {
      S |= mask[a[i]];
    }
    if (!S.test(m - 1)) {
      ++ans;
    }
  }
  std::cout << ans << "\n";
}
