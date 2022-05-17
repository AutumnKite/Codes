#include <bits/stdc++.h>

template<typename Tp>
constexpr Tp INF = std::numeric_limits<Tp>::max();

class set {
  std::multiset<int> S;
  int min, max;

public:
  set() : min(INF<int>), max(-INF<int>) {}

  void insert(int x) {
    S.insert(x);
    min = std::min(min, x);
    max = std::max(max, x);
  }

  void erase(int x) {
    S.erase(S.find(x));
    if (S.empty()) {
      min = INF<int>;
      max = -INF<int>;
    } else {
      min = *S.begin();
      max = *S.rbegin();
    }
  }

  long long query(long long A, long long B, int C, int y) const {
    if (S.empty()) {
      return -INF<long long>;
    }
    long long t = A + 1ll * C * y;
    if (t > 0) {
      return t * max + B * y;
    } else {
      return t * min + B * y;
    }
  }
};

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        std::cin >> a[i][j];
      }
    }
    std::vector<std::vector<int>> p(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        std::cin >> p[i][j];
      }
    }
  
    std::vector<int> w(n * n), l(n * n);
    std::vector<int> cnt(n * n);
    std::map<int, set> mp;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        w[p[i][j]] += a[i][j];
        ++cnt[p[i][j]];
        for (int d = 0; d < 4; ++d) {
          int x = i + dx[d], y = j + dy[d];
          if (0 <= x && x < n && 0 <= y && y < n && a[x][y] != a[i][j]) {
            ++l[p[i][j]];
          }
        }
      }
    }
    for (int i = 0; i < n * n; ++i) {
      if (cnt[i]) {
        mp[l[i]].insert(w[i]);
      }
    }

    auto erase = [&](int i, int j) {
      w[p[i][j]] -= a[i][j];
      --cnt[p[i][j]];
      for (int d = 0; d < 4; ++d) {
        int x = i + dx[d], y = j + dy[d];
        if (0 <= x && x < n && 0 <= y && y < n && a[x][y] != a[i][j]) {
          --l[p[i][j]];
        }
      }
    };

    int q;
    std::cin >> q;
    while (q--) {
      int i, j, x;
      std::cin >> i >> j >> x;
      --i, --j;
      if (p[i][j] != x) {
        
      }
    }
  }
}
