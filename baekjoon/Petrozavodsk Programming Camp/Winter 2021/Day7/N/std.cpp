#include <bits/stdc++.h>

const char name[] = "RGB";

// char p[100];
// int idx;

int get() {
  char c;
  std::cin >> c;
  // c = p[--idx];
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
    // idx = 0;
    // for (int i = 0; i < A; ++i) {
    //   p[idx++] = name[0];
    // }
    // for (int i = 0; i < B; ++i) {
    //   p[idx++] = name[1];
    // }
    // for (int i = 0; i < C; ++i) {
    //   p[idx++] = name[2];
    // }
    // std::shuffle(p, p + idx, std::mt19937(time(0)));
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
      // int size[3] = {};
      for (int i = 0; i < 100; ++i) {
        int x = get();
        if (id[x]) {
          std::cout << "PLACE " << id[x] << std::endl;
          // ++size[id[x]];
          ++cnt[x];
        } else {
          int ymin = (x + 1) % 3, ymax = (x + 2) % 3;
          if (cnt[ymin] > cnt[ymax]) {
            std::swap(ymin, ymax);
          }
          if (cnt[x] >= cnt[ymin]) {
            std::cout << "EMPTY " << id[ymin] << std::endl;
            // size[id[ymin]] = 0;
            cnt[ymin] = cnt[x] = 0;
            std::swap(id[ymin], id[x]);
            std::cout << "PLACE " << id[x] << std::endl;
            // ++size[id[x]];
            ++cnt[x];
          } else {
            std::cout << "DISCARD" << std::endl;
            ++cnt[x];
          }
        }
      }
      // std::cerr << size[1] << " " << size[2] << "\n";
    }
  }
}
