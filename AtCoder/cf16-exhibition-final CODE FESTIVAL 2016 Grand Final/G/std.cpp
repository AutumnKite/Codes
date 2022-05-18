#include <bits/stdc++.h>

using u64 = uint64_t;

u64 C[701][9];

void init() {
  C[0][0] = 1;
  for (int i = 1; i <= 700; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= 8; ++j) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  init();

  u64 L;
  std::cin >> L;
  std::string s;
  int n = 600;
  while (n) {
    while (L >= C[n + 6][7]) {
      s += 'F';
      L -= C[n + 6][7];
    }
    if (!s.empty()) {
      s += "ESTIVAL";
    }
    --n;
  }
  std::cout << s << "\n";
}
