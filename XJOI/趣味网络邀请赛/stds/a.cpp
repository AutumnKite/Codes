#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;

void Print(int x, int y) {
  if (n < m) {
    printf("%d %d\n", x + 1, y + 1);
  } else {
    printf("%d %d\n", m - y, x + 1);
  }
}

int main(void) {
  scanf("%d", &n);
  m = n + 1;
  printf("%d\n", n * m - 1);
  if (n & 1) {
    swap(n, m);
  }
  for (int y = 0; y < m - 1; y += 2) {
    for (int x = 0; x < n; x += 2) {
      Print(x, y);
      Print(x + 1, y + 1);
    }
    for (int x = n - 2; x >= 0; x -= 2) {
      Print(x + 1, y);
      Print(x, y + 1);
    }
  }
  for (int x = 0; x < n; ++x) {
    Print(x, m - 1);
  }
  return 0;
}
