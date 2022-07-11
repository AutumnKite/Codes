#include <bits/stdc++.h>

int calc(int x, int y) {
  return ((std::abs(x) + 1) ^ (std::abs(y) + 1)) + 1;
}

const char name[] = "LRDU";
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

class path {
  std::vector<std::pair<int, int>> Q;
  std::map<std::pair<int, int>, int> cnt;
  long long ans;

public:
  path(std::string s, int x, int y) : ans() {
    Q.emplace_back(x, y);
    for (char c : s) {
      int k = std::find(name, name + 4, c) - name;
      x += dx[k], y += dy[k];
      Q.emplace_back(x, y);
    }
    std::reverse(Q.begin(), Q.end());
    for (auto p : Q) {
      ans += (++cnt[p]) * calc(p.first, p.second);
    }
  }

  void next() {
    auto p = Q.back();
    ans -= (cnt[p]--) * calc(p.first, p.second);
    Q.pop_back();
  }

  void add(int x, int y) {
    std::pair<int, int> p(x, y);
    ans += (++cnt[p]) * calc(p.first, p.second);
  }

  long long get_ans() const {
    return ans;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<path> T;
  for (int i = 0; i < 4; ++i) {
    T.emplace_back(s, -dx[i], -dy[i]);
  }
  for (int i = 0; i < 4; ++i) {
    T[i].next();
  }
  int x = 0, y = 0;
  for (char c : s) {
    for (int i = 0; i < 4; ++i) {
      T[i].next();
    }
    int k = std::find(name, name + 4, c) - name;
    for (int i = 0; i < 4; ++i) {
      T[i].add(x, y);
    }
    x += dx[k], y += dy[k];
    std::cout << T[k].get_ans() << "\n";
  }
}
