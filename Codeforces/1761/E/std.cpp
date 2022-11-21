#include <bits/stdc++.h>

class disjoint_set {
public:
  typedef std::size_t size_type;

protected:
  std::vector<size_type> fa;

public:
  disjoint_set(size_type n = 0) : fa(n) {
    std::iota(fa.begin(), fa.end(), 0);
  }

  size_type find(size_type x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
  }

  bool merge(size_type x, size_type y) {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    fa[y] = x;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<int> deg(n);
    disjoint_set D(n);
    int cnt = n;
    for (int i = 0; i < n; ++i) {
      std::string b;
      std::cin >> b;
      for (int j = i + 1; j < n; ++j) {
        if (b[j] == '1') {
          ++deg[i];
          ++deg[j];
          cnt -= D.merge(i, j);
        }
      }
    }
    if (cnt == 1) {
      std::cout << 0 << "\n";
      continue;
    }
    std::vector<std::vector<int>> p(n);
    for (int i = 0; i < n; ++i) {
      p[D.find(i)].push_back(i);
    }
    std::vector<int> all;
    bool ok = false;
    for (int i = 0; i < n; ++i) {
      if (!p[i].empty()) {
        all.push_back(i);
        int min = i;
        for (int u : p[i]) {
          if (deg[u] < deg[min]) {
            min = u;
          }
        }
        if (deg[min] < (int)p[i].size() - 1 || !deg[min]) {
          std::cout << 1 << "\n";
          std::cout << min + 1 << "\n";
          ok = true;
          break;
        }
      }
    }
    if (ok) {
      continue;
    }
    if (all.size() > 2) {
      std::cout << 2 << "\n";
      std::cout << all[0] + 1 << " " << all[1] + 1 << "\n";
    } else {
      int which = p[all[0]].size() > p[all[1]].size();
      std::cout << p[all[which]].size() << "\n";
      for (int x : p[all[which]]) {
        std::cout << x + 1 << " ";
      }
      std::cout << "\n";
    }
  }
}
