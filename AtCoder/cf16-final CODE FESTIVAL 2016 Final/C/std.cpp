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

  int n, m;
  std::cin >> n >> m;
  disjoint_set D(n);
  std::vector<int> lst(m, -1);
  for (int i = 0; i < n; ++i) {
    int k;
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      int c;
      std::cin >> c;
      --c;
      if (lst[c] != -1) {
        D.merge(lst[c], i);
      }
      lst[c] = i;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (D.find(i) != D.find(0)) {
      std::cout << "NO\n";
      return 0;
    }
  }
  std::cout << "YES\n";
}
