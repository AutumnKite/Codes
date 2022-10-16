#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> l(m), r(m);
  std::vector<long long> v(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> l[i] >> r[i] >> v[i];
    --l[i];
  }
  std::vector<int> ans(m, 1);
  for (int k = 0; k < 60; ++k) {
    std::vector<int> c(n + 1);
    std::vector<long long> ci(n + 1);
    for (int i = 0; i < m; ++i) {
      if (v[i] >> k & 1) {
        ++c[l[i]], --c[r[i]];
        ci[l[i]] += i, ci[r[i]] -= i;
      }
    }
    for (int i = 0; i < n; ++i) {
      c[i + 1] += c[i];
      ci[i + 1] += ci[i];
    }
    std::vector<int> sum(n + 1), sumi(n + 1), lst(n);
    for (int i = 0; i < n; ++i) {
      if (c[i] != 1) {
        ci[i] = -1;
      }
      sum[i + 1] = sum[i] + !c[i];
      sumi[i + 1] = sumi[i] + (ci[i] != -1);
      if (i > 0 && (ci[i] == -1 || ci[i] == ci[lst[i - 1]])) {
        lst[i] = lst[i - 1];
      } else {
        lst[i] = i;
      }
    }
    std::vector<int> id;
    for (int i = 0; i < m; ++i) {
      if (!(v[i] >> k & 1) && sum[r[i]] == sum[l[i]]) {
        id.push_back(i);
      }
    }
    if (id.empty()) {
      continue;
    }
    std::vector<int> s(m);
    if (id.size() == 1) {
      s[id[0]] = 1;
    }
    std::vector<int> d(n + 1);
    for (int i : id) {
      if (sumi[r[i]] > sumi[l[i]]) {
        ++d[lst[l[i]]], --d[r[i]];
      }
    }
    for (int i = 0; i < n; ++i) {
      d[i + 1] += d[i];
    }
    for (int i = 0; i < n; ++i) {
      if (ci[i] != -1 && lst[i] == i && d[i] == (int)id.size()) {
        s[ci[i]] = 1;
      }
    }
    for (int i = 0; i < m; ++i) {
      ans[i] &= s[i];
    }
  }
  for (int i = 0; i < m; ++i) {
    std::cout << ans[i];
  }
  std::cout << "\n";
}
/*
2 3
1 2 1
2 2 0
2 2 1
*/
