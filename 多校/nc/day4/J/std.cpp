#include <bits/stdc++.h>

struct operation {
  int op, l, r, id;

  operation(int t_op, int t_l, int t_r, int t_id)
      : op(t_op), l(t_l), r(t_r), id(t_id) {
    if (l > r) {
      std::swap(l, r);
    }
  }
};

long long arith(int l, int r) {
  if (l > r) {
    return 0;
  }
  return 1ll * (l + r) * (r - l + 1) / 2;
}

long long arith2(int l, int r) {
  if (l > r) {
    return 0;
  }
  return (arith(l, r) - (r + 1) / 2 + l / 2) / 2;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;
  std::vector<std::vector<operation>> Q(2000001);
  for (int i = 0; i < q; ++i) {
    int op, sx, sy, tx, ty;
    std::cin >> op >> sx >> sy >> tx >> ty;
    --op;
    Q[sx + sy].emplace_back(op, sx, tx, i);
  }

  std::vector<long long> ans(q);
  for (int s = 0; s <= 2000000; ++s) {
    if (Q[s].empty()) {
      continue;
    }

    auto calc = [&](int l, int r) -> long long {
      long long res = arith(1, r - l);
      res += arith(l, std::min(s / 3, r / 2));
      res += arith(1, r - std::max({l, 2 * r - s, r / 2 + 1}));
      res += arith2(s - std::min(2 * r - s - 1, r), s - std::max(s / 3 + 1, l));
      return res;
    };

    std::map<int, int> mp;

    auto insert = [&](int l, int r) {
      long long res = 0;
      auto it = mp.upper_bound(l);
      if (it != mp.begin()) {
        auto pr = std::prev(it);
        if (pr->second == l) {
          l = pr->first;
          res -= calc(pr->first, pr->second);
          mp.erase(pr);
        }
      }
      if (it != mp.end() && it->first == r) {
        r = it->second;
        res -= calc(it->first, it->second);
        mp.erase(it);
      }
      res += calc(l, r);
      mp[l] = r;
      return res;
    };

    auto erase = [&](int l, int r) {
      auto it = --mp.upper_bound(l);
      int L = it->first, R = it->second;
      mp.erase(it);
      long long res = -calc(L, R);
      if (L < l) {
        res += calc(L, l);
        mp[L] = l;
      }
      if (r < R) {
        res += calc(r, R);
        mp[r] = R;
      }
      return res;
    };

    for (auto p : Q[s]) {
      if (p.op == 0) {
        ans[p.id] = insert(p.l, p.r);
      } else {
        ans[p.id] = erase(p.l, p.r);
      }
    }
  }
  for (int i = 1; i < q; ++i) {
    ans[i] += ans[i - 1];
  }
  for (int i = 0; i < q; ++i) {
    std::cout << ans[i] << "\n";
  }
}
