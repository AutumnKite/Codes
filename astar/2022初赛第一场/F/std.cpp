#include <bits/stdc++.h>

long long get_ans(long long a, long long b) {
  if (b == 0) {
    return 0;
  }
  return a / b * 2 + get_ans(b, a % b);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n, m;
  std::cin >> n >> m;
  std::cout << get_ans(m, n - m) << "\n";
}
