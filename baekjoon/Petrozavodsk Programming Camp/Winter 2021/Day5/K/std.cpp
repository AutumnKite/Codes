#include <bits/stdc++.h>

template<typename T>
class set {
  std::priority_queue<T, std::vector<T>, std::greater<T>> Q, R;

public:
  set() : Q(), R() {}

  void insert(const T &x) {
    Q.push(x);
  }

  void erase(const T &x) {
    R.push(x);
  }

  bool empty() const {
    return Q.size() == R.size();
  }

  T top() {
    while (!R.empty() && Q.top() == R.top()) {
      Q.pop();
      R.pop();
    }
    return Q.top();
  }
};

constexpr int INF = std::numeric_limits<int>::max() / 2;

struct node {
  int l, r, max;
  set<int> S;
};

class segtree {
  constexpr static int enlarge(int n) {
    int res = 1;
    while (res < n) {
      res <<= 1;
    }
    return res;
  }

protected:
  const int n, en;

  std::vector<node> val;

  void up(int u) {
    int top = val[u].S.empty() ? INF : val[u].S.top();
    if (val[u].l + 1 == val[u].r) {
      val[u].max = top;
      return;
    }
    int ls = u << 1, rs = u << 1 | 1;
    val[u].max = std::max(val[ls].max, val[rs].max);
    if (top < val[u].max) {
      val[u].max = top;
    }
  }

  void build(int u, int l, int r) {
    val[u].l = l, val[u].r = r;
    if (l + 1 == r) {
      val[u].max = INF;
      return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid, r);
    up(u);
  }

  void insert(int u, int l, int r, int L, int R, int x) {
    if (L <= l && r <= R) {
      val[u].S.insert(x);
      up(u);
      return;
    }
    int mid = (l + r) >> 1;
    if (L < mid) {
      insert(u << 1, l, mid, L, R, x);
    }
    if (mid < R) {
      insert(u << 1 | 1, mid, r, L, R, x);
    }
    up(u);
  }

  void erase(int u, int l, int r, int L, int R, int x) {
    if (L <= l && r <= R) {
      val[u].S.erase(x);
      up(u);
      return;
    }
    int mid = (l + r) >> 1;
    if (L < mid) {
      erase(u << 1, l, mid, L, R, x);
    }
    if (mid < R) {
      erase(u << 1 | 1, mid, r, L, R, x);
    }
    up(u);
  }

  int query(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
      return val[u].max;
    }
    int mid = (l + r) >> 1;
    int res;
    if (R <= mid) {
      res = query(u << 1, l, mid, L, R);
    } else if (L >= mid) {
      res = query(u << 1 | 1, mid, r, L, R);
    } else {
      res = std::max(query(u << 1, l, mid, L, R),
                     query(u << 1 | 1, mid, r, L, R));
    }
    if (!val[u].S.empty()) {
      res = std::min(res, val[u].S.top());
    }
    return res;
  }

public:
  segtree(int t_n)
  : n(t_n), en(enlarge(n)), val(en << 1) {
    if (n) {
      build(1, 0, n);
    }
  }

  void insert(int l, int r, int x) {
    if (l < r) {
      insert(1, 0, n, l, r, x);
    }
  }

  void erase(int l, int r, int x) {
    if (l < r) {
      erase(1, 0, n, l, r, x);
    }
  }

  int query_max(int l, int r) {
    return query(1, 0, n, l, r);
  }
};

const int L = 200001;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int q;
  std::cin >> q;

  std::vector<std::map<int, int>> mp(L);
  segtree T(L);

  auto erase = [&](int x, int l, int r) {
    auto it = mp[x].lower_bound(l);
    if (it != mp[x].begin()) {
      auto pr = std::prev(it);
      int t = pr->second;
      if (t > l) {
        int nl = pr->first;
        T.erase(nl, t, x);
        if (t > r) {
          pr->second = l;
          mp[x].emplace(r, t);
          T.insert(r, t, x);
          T.insert(nl, l, x);
          return;
        } else {
          pr->second = l;
          T.insert(nl, l, x);
        }
      }
    }
    while (it != mp[x].end() && it->first < r) {
      int t = it->second;
      T.erase(it->first, it->second, x);
      it = mp[x].erase(it);
      if (t > r) {
        mp[x].emplace(r, t);
        T.insert(r, t, x);
        return;
      }
    }
  };

  for (int i = 0; i < q; ++i) {
    mp[i].emplace(0, L);
    T.insert(0, L, i);
  }
  long long S = 0;
  for (int k = 0; k < q; ++k) {
    int op;
    std::cin >> op;
    if (op == 1) {
      long long x, l, r;
      std::cin >> x >> l >> r;
      x ^= S, l ^= S, r ^= S;
      ++r;
      erase(x, l, r);
    } else {
      long long l, r;
      std::cin >> l >> r;
      l ^= S, r ^= S;
      ++r;
      int ans = T.query_max(l, r);
      std::cout << ans << "\n";
      S += ans;
    }
  }
}
