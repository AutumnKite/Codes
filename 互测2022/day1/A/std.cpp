#include <bits/stdc++.h>

template<typename Iter>
auto planting_trees(Iter first, Iter last) {
  using Tp = typename std::iterator_traits<Iter>::value_type;
  std::vector<Tp> a(first, last);
  std::vector<bool> vis(a.size()); 
  std::list<std::size_t> l;
  for (std::size_t i = 0; i < a.size(); ++i) {
    l.push_back(i);
  }
  using iter = typename decltype(l)::iterator;
  std::vector<iter> its;
  std::priority_queue<std::pair<Tp, std::size_t>> Q;
  for (auto i = l.begin(); i != l.end(); ++i) {
    Q.emplace(a[*i], its.size());
    its.push_back(i);
  }
  std::vector<Tp> ans(1, 0);
  Tp now = 0;
  while (!Q.empty()) {
    auto i = Q.top().second;
    Q.pop();
    if (vis[i]) {
      continue;
    }
    now += a[i];
    ans.push_back(now);
    auto it = its[i];
    bool ok = true;
    Tp v = 0;
    if (it != l.begin()) {
      auto prev = std::prev(it);
      v += a[*prev];
      vis[*prev] = true;
      l.erase(prev);
    } else {
      ok = false;
    }
    if (std::next(it) != l.end()) {
      auto next = std::next(it);
      v += a[*next];
      vis[*next] = true;
      l.erase(next);
    } else {
      ok = false;
    }
    if (!ok) {
      vis[*it] = true;
      l.erase(it);
      continue;
    }
    v -= a[i];
    a[i] = v;
    Q.emplace(a[i], i);
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  int now = 0;
  for (int i = 0; i < n; ++i) {
    now += s[i] == '1';
  }
  std::vector<int> ans(n);
  ans[0] = now;
  for (int i = 0; i <= n; ++i) {
    now += s[i] == '0';
    now -= s[i] == '1';
    ans[0] = std::max(ans[0], now);
  }
  std::vector<int> a;
  int len = 0;
  for (int i = 0; i < n; ++i) {
    ++len;
    if (i + 1 == n || s[i + 1] != s[i]) {
      a.push_back(-len);
      len = 0;
    }
  }
  if (a.size() >= 2) {
    for (int S = 0; S < 4; ++S) {
      if (a.size() == 2 && S == 3) {
        continue;
      }
      int x = 0;
      int sum = 0;
      int l = 1, r = a.size() - 1;
      if (S & 1) {
        ++x;
        sum += a[0];
        l = std::min(r, l + 1);
      }
      if (S & 2) {
        ++x;
        sum += a.back();
        r = std::max(l, r - 1);
      }
      auto d = planting_trees(a.begin() + l, a.begin() + r);
      for (int i = 0; i < (int)d.size(); ++i) {
        int m = (int)a.size() - x - 1;
        if (m >= 2) {
          ans[m - 1] = std::max(ans[m - 1], n + d[i] + sum);
        }
        x += 2;
      }
    }
  }
  std::cout << ans[0];
  for (int i = 1; i < n; ++i) {
    ans[i] = std::max(ans[i], ans[i - 1]);
    std::cout << " " << ans[i];
  }
  std::cout << "\n";
}
