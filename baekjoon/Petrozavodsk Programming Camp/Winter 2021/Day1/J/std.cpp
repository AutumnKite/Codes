#include <bits/stdc++.h>

template<typename Tp>
constexpr Tp INF = std::numeric_limits<Tp>::max();

class set {
  std::multiset<int> S;

public:
  set() {}

  void insert(int x) {
    S.insert(x);
  }

  void erase(int x) {
    S.erase(S.find(x));
  }

  bool empty() const {
    return S.empty();
  }

  long long query(long long A, long long B, int C, int y) const {
    if (S.empty()) {
      return -INF<long long>;
    }
    long long t = A + 1ll * C * y;
    if (t > 0) {
      return t * *S.rbegin() + B * y;
    } else {
      return t * *S.begin() + B * y;
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
          if (0 <= x && x < n && 0 <= y && y < n && p[x][y] != p[i][j]) {
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
      mp[l[p[i][j]]].erase(w[p[i][j]]);
      if (mp[l[p[i][j]]].empty()) {
        mp.erase(l[p[i][j]]);
      }
      w[p[i][j]] -= a[i][j];
      --cnt[p[i][j]];
      for (int d = 0; d < 4; ++d) {
        int x = i + dx[d], y = j + dy[d];
        if (0 <= x && x < n && 0 <= y && y < n) {
          if (p[i][j] != p[x][y]) {
            --l[p[i][j]];
          } else {
            ++l[p[i][j]];
          }
        }
      }
      if (cnt[p[i][j]]) {
        mp[l[p[i][j]]].insert(w[p[i][j]]);
      }
    };

    auto insert = [&](int i, int j) {
      if (cnt[p[i][j]]) {
        mp[l[p[i][j]]].erase(w[p[i][j]]);
        if (mp[l[p[i][j]]].empty()) {
          mp.erase(l[p[i][j]]);
        }
      }
      w[p[i][j]] += a[i][j];
      ++cnt[p[i][j]];
      for (int d = 0; d < 4; ++d) {
        int x = i + dx[d], y = j + dy[d];
        if (0 <= x && x < n && 0 <= y && y < n) {
          if (p[i][j] != p[x][y]) {
            ++l[p[i][j]];
          } else {
            --l[p[i][j]];
          }
        }
      }
      mp[l[p[i][j]]].insert(w[p[i][j]]);
    };

    int q;
    std::cin >> q;
    while (q--) {
      int i, j, x;
      long long A, B, C;
      std::cin >> i >> j >> x >> A >> B >> C;
      --i, --j;
      if (p[i][j] != x) {
        erase(i, j);
        p[i][j] = x;
        insert(i, j);
      }
      long long ans = -INF<long long>;
      for (const auto &[v, s] : mp) {
        ans = std::max(ans, s.query(A, B, C, v));
      }
      std::cout << ans << " \n"[q == 0];
    }
  }
}
