#include <bits/stdc++.h>

using i64 = int64_t;

constexpr i64 INF = std::numeric_limits<i64>::max() / 2;

i64 plus(i64 a, i64 b) {
  return std::min(a + b, INF);
}

void inc(i64 &a, i64 b) {
  a = std::min(a + b, INF);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int k;
  i64 n;
  std::cin >> k >> n;

  i64 m = 1;
  for (int i = 1; i <= k; ++i) {
    m *= 10;
  }

  std::vector<std::vector<i64>> f(1, std::vector<i64>(m));
  int i = 0;
  f[0][0] = 1;
  for (; f[i][0] <= n; ++i) {
    f.emplace_back(m);
    for (int j = 0; j < m; ++j) {
      if (f[i][j]) {
        for (int k = 0; k < 10; ++k) {
          i64 v = k * (m - 1) + j;
          if (v % 10 != 9) {
            inc(f[i + 1][v / 10], f[i][j]);
          }
        }
      }
    }
  }

  std::vector<i64> st;
  std::vector<int> ans;
  st.push_back(0);
  while (i--) {
    int v = 0;
    for (; v < 10; ++v) {
      i64 sum = 0;
      for (i64 t : st) {
        for (int x = 0; x < 9; ++x) {
          i64 j = t * 10 + x - v * (m - 1);
          if (0 <= j && j < m) {
            inc(sum, f[i][j]);
          }
        }
      }
      if (sum <= n) {
        n -= sum;
      } else {
        break;
      }
    }
    if (!ans.empty() || v) {
      ans.push_back(v);
    }
    std::vector<i64> nst;
    for (i64 t : st) {
      for (int x = 0; x < 9; ++x) {
        i64 j = t * 10 + x - v * (m - 1);
        if (0 <= j && j < m && f[i][j]) {
          nst.push_back(j);
        }
      }
    }
    st.swap(nst);
  }
  for (int x : ans) {
    std::cout << x;
  }
  std::cout << "\n";
}
