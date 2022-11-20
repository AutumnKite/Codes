#include <bits/stdc++.h>

template<typename Val>
class fast_copy_array {
public:
  typedef std::size_t size_type;

protected:
  size_type n;

  struct node {
    node *ls, *rs;
    Val v;

    node() : ls(), rs(), v() {}
  };

  node *rt;

  void add(node *&u, size_type l, size_type r, size_type x, const Val &v) {
    if (u == nullptr) {
      u = new node();
    } else {
      u = new node(*u);
    }
    u->v += v;
    if (l + 1 == r) {
      return;
    }
    size_type mid = (l + r) >> 1;
    if (x < mid) {
      add(u->ls, l, mid, x, v);
    } else {
      add(u->rs, mid, r, x, v);
    }
  }

  Val query(node *u, size_type l, size_type r, size_type L, size_type R) const {
    if (u == nullptr) {
      return Val();
    }
    if (L <= l && r <= R) {
      return u->v;
    }
    size_type mid = (l + r) >> 1;
    if (R <= mid) {
      return query(u->ls, l, mid, L, R);
    } else if (L >= mid) {
      return query(u->rs, mid, r, L, R);
    } else {
      return query(u->ls, l, mid, L, R) + query(u->rs, mid, r, L, R);
    }
  }

public:
  fast_copy_array(size_type n) : n(n), rt(nullptr) {}

  void add(size_type x, const Val &v) {
    add(rt, 0, n, x, v);
  }

  Val query(size_type l, size_type r) const {
    return query(rt, 0, n, l, r);
  }
};

std::vector<int> manacher(const std::string &s) {
  int n = s.size();
  std::vector<int> h(n);
  for (int i = 0, m = 0, r = 0; i < n; ++i) {
    if (i < r) {
      h[i] = std::min(h[2 * m - i], r - i);
    } else {
      h[i] = 0;
    }
    while (i - h[i] >= 0 && i + h[i] < n && s[i - h[i]] == s[i + h[i]]) {
      ++h[i];
    }
    if (i + h[i] > r) {
      m = i, r = i + h[i];
    }
  }
  return h;
}

int calc(const std::string &s) {
  auto h = manacher(s);
  int n = s.size();
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (i + h[i] >= n) {
      ++cnt;
    }
  }
  return cnt - 1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;
  s = [&]() {
    std::string t = "#";
    for (char c : s) {
      t += c;
      t += '#';
    }
    return t;
  }();
  int n = s.size();
  auto h = manacher(s);
  std::vector<fast_copy_array<int>> pre(n + 1, n + 1);
  for (int i = 0; i < n; ++i) {
    pre[i + 1] = pre[i];
    pre[i + 1].add(i + h[i], 1);
  }

  int q;
  std::cin >> q;
  int ans = 0;
  int lim = 200000000 / q;
  lim += !(lim & 1);
  bool flag = false;
  while (q--) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int x;
      char c;
      std::cin >> x >> c;
      x ^= ans;
      --x;
      x = x * 2 + 1;
      s[x] = c;
      flag = true;
    } else {
      int l, r;
      std::cin >> l >> r;
      l ^= ans, r ^= ans;
      --l;
      l = l * 2;
      r = r * 2 + 1;
      if (flag) {
        l = std::max(l, r - lim);
        ans = calc(s.substr(l, r - l));
        std::cout << ans << "\n";
      } else {
        ans = pre[r - 1].query(r, n + 1) - pre[(l + r) / 2].query(r, n + 1);
        std::cout << ans << "\n";
      }
    }
  }
}
