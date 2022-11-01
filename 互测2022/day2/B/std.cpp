#include <bits/stdc++.h>

using u64 = uint64_t;

std::mt19937_64 rnd(time(0));

class tree {
  int n;
  std::vector<u64> a;
  std::vector<std::vector<int>> E;

public:
  tree(const std::vector<u64> &ta) : n(ta.size()), a(ta), E(n) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
  }

  std::vector<u64> solve() const {
    std::vector<u64> all;
    all.reserve(n * (n + 1) / 2);
    for (int rt = 0; rt < n; ++rt) {
      auto dfs = [&](auto &self, int u, int fa, u64 sum) -> void {
        sum += a[u];
        if (rt <= u) {
          all.push_back(sum);
        }
        for (int v : E[u]) {
          if (v != fa) {
            self(self, v, u, sum);
          }
        }
      };
      dfs(dfs, rt, -1, 0);
    }
    std::sort(all.begin(), all.end());
    return all;
  }
};

const int N = 200005, LG = 18;

int n;
int fa1[N], fa2[N];
std::vector<int> E1[N], E2[N];
int map[N];
int a[N];
int p[N];

void init() {
  for (int i = 2; i <= n; ++i) {
    std::cin >> fa1[i];
    E1[fa1[i]].push_back(i);
    E1[i].push_back(fa1[i]);
  }
  for (int i = 2; i <= n; ++i) {
    std::cin >> fa2[i];
    E2[fa2[i]].push_back(i);
    E2[i].push_back(fa2[i]);
  }
  int u = 1;
  while (E1[u].size() == 2) {
    ++u;
  }
  int lst = -1;
  for (int i = 1; i <= n; ++i) {
    map[u] = i;
    int nxt = -1;
    for (int v : E1[u]) {
      if (v != lst) {
        nxt = v;
        break;
      }
    }
    lst = u, u = nxt;
  }
  u = 1;
  while (E2[u].size() == 2) {
    ++u;
  }
  lst = -1;
  for (int i = 1; i <= n; ++i) {
    a[i] = map[u];
    int nxt = -1;
    for (int v : E2[u]) {
      if (v != lst) {
        nxt = v;
        break;
      }
    }
    lst = u, u = nxt;
  }
}

struct Interval {
  int l, r;

  Interval() {}

  Interval(int _l, int _r) : l(_l), r(_r) {}
};

Interval operator+(const Interval &a, const Interval &b) {
  return Interval(std::min(a.l, b.l), std::max(a.r, b.r));
}

int Log[N];
Interval st[LG][N];

void initST() {
  Log[1] = 0;
  for (int i = 2; i <= n; ++i) {
    Log[i] = Log[i >> 1] + 1;
  }
  for (int i = 1; i <= n; ++i) {
    st[0][i] = Interval(p[i], p[i]);
  }
  for (int j = 1; j < LG; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
      st[j][i] = st[j - 1][i] + st[j - 1][i + (1 << (j - 1))];
    }
  }
}

Interval query(int l, int r) {
  int t = Log[r - l + 1];
  return st[t][l] + st[t][r - (1 << t) + 1];
}

struct Node {
  Interval I, ran, fsup, sup;
};

Node operator+(const Node &a, const Node &b) {
  Node res;
  res.I = a.I + b.I;
  res.ran = a.ran + b.ran;
  res.fsup = a.fsup + b.fsup;
  res.sup = a.fsup + b.sup;
  return res;
}

bool check(const Node &a) {
  return a.I.r - a.I.l == a.ran.r - a.ran.l;
}

int cnt;
bool type[N * 2];
Node nd[N * 2];
std::vector<int> E[N * 2];

int top, sta[N];
int fail[N];
Node fail_nd[N];

int rt;

int add(int u) {
  if (!top) {
    sta[++top] = u;
    fail[top] = 0;
    fail_nd[top] = nd[u];
    return 0;
  }
  int v = sta[top];
  Node tmp = nd[v] + nd[u];
  if (type[v] && !E[v].empty() && check(nd[E[v].back()] + nd[u])) {
    nd[v] = tmp;
    E[v].push_back(u);
    --top;
    return v;
  }
  if (check(tmp)) {
    nd[++cnt] = tmp;
    type[cnt] = true;
    E[cnt].push_back(v);
    E[cnt].push_back(u);
    --top;
    return cnt;
  }
  if (tmp.sup.r > nd[u].I.r) {
    sta[++top] = u;
    fail[top] = top - 1;
    fail_nd[top] = nd[u];
    return 0;
  }
  int t = top;
  tmp = nd[u];
  do {
    tmp = fail_nd[t] + tmp;
    t = fail[t];
  } while (tmp.sup.r <= nd[u].I.r && !check(tmp));
  if (check(tmp)) {
    nd[++cnt] = tmp;
    type[cnt] = false;
    for (int i = t + 1; i <= top; ++i) {
      E[cnt].push_back(sta[i]);
    }
    E[cnt].push_back(u);
    top = t;
    return cnt;
  }
  sta[++top] = u;
  fail[top] = t;
  fail_nd[top] = tmp;
  return 0;
}

long long ans = 0;

void dfs(int u) {
  int len = E[u].size();
  if (type[u] && len) {
    ans += 1ll * len * (len - 1) / 2;
  } else {
    ans += 1;
  }
  for (int i = 0; i < len; ++i) {
    int v = E[u][i];
    dfs(v);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;

  if (n <= 5000) {
    std::vector<u64> a(n);
    for (int i = 0; i < n; ++i) {
      a[i] = rnd();
    }
    tree S(a), T(a);
    for (int i = 1; i < n; ++i) {
      int x;
      std::cin >> x;
      --x;
      S.add_edge(x, i);
    }
    for (int i = 1; i < n; ++i) {
      int x;
      std::cin >> x;
      --x;
      T.add_edge(x, i);
    }
    auto A = S.solve(), B = T.solve();
    int size = n * (n + 1) / 2;
    int ans = 0;
    for (int i = 0, j = 0; i < size; ++i) {
      while (j < size && B[j] < A[i]) {
        ++j;
      }
      ans += j < size && A[i] == B[j];
    }
    std::cout << ans << "\n";
    return 0;
  }

  init();
  for (int i = 1; i <= n; ++i) {
    p[a[i]] = i;
  }

  initST();

  cnt = n;
  for (int i = 1; i <= n; ++i) {
    nd[i].I = Interval(i, i);
    nd[i].ran = Interval(a[i], a[i]);
    if (i < n) {
      int l = a[i], r = a[i + 1];
      if (l > r) {
        std::swap(l, r);
      }
      nd[i].fsup = query(l, r);
    } else {
      nd[i].fsup = Interval(n + 1, 0);
    }
    nd[i].sup = Interval(n + 1, 0);
    type[i] = true;
  }
  for (int i = 1; i <= n; ++i) {
    int x = i;
    while (x) {
      x = add(x);
    }
  }

  rt = sta[1];
  dfs(rt);
  std::cout << ans << "\n";
}
/*
7
6 1 3 7 4 2
3 4 7 1 2 1
*/
