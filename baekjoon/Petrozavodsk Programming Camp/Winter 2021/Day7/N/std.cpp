#include <bits/stdc++.h>

const char name[] = "RGB";

int get() {
  char c;
  std::cin >> c;
  return std::find(name, name + 3, c) - name;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int A, B, C;
    std::cin >> A >> B >> C;
    if (100 - std::max({A, B, C}) >= 43) {
      for (int i = 0; i < 100; ++i) {
        int x = get();
        if (x) {
          std::cout << "PLACE " << x << std::endl;
        } else {
          std::cout << "DISCARD" << std::endl;
        }
      }
    } else {
      int cnt[3] = {};
      int id[3] = {0, 1, 2};
      for (int i = 0; i < 100; ++i) {
        int x = get();
        if (id[x]) {
          std::cout << "PLACE " << id[x] << std::endl;
          ++cnt[x];
        } else {
          int ymin = (x + 1) % 3, ymax = (x + 2) % 3;
          if (cnt[ymin] > cnt[ymax]) {
            std::swap(ymin, ymax);
          }
          if (cnt[x] >= cnt[ymax]) {
            std::cout << "EMPTY " << id[ymin] << std::endl;
            cnt[ymin] = cnt[x] = 0;
            std::swap(id[ymin], id[x]);
            std::cout << "PLACE " << id[x] << std::endl;
            ++cnt[x];
          } else {
            std::cout << "DISCARD" << std::endl;
          }
        }
      }
    }
  }
}
