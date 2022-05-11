#include <bits/stdc++.h>

int main() {
  int H, W;
  std::cin >> H >> W;
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      std::string s;
      std::cin >> s;
      if (s == "snuke") {
        std::cout << char('A' + j) << 1 + i << "\n";
      }
    }
  }
}