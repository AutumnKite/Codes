#include <bits/stdc++.h>

constexpr int INF = std::numeric_limits<int>::max() / 2;

struct state_suf {
  int pos, max, pre;
};

std::vector<int> trans_suf(const std::vector<int> &a,
                           const std::vector<int> &f) {
  int n = a.size();
  std::vector<int> g(n + 1, -INF);
  std::vector<state_suf> sta;
  for (int i = 0; i < n; ++i) {
    state_suf now;
    now.pos = i;
    now.max = f[i];
    while (!sta.empty() && a[sta.back().pos] < a[i]) {
      now.max = std::max(now.max, sta.back().max);
      sta.pop_back();
    }
    now.pre = now.max - (int)sta.size();
    if (!sta.empty()) {
      now.pre = std::max(now.pre, sta.back().pre);
    }
    sta.push_back(now);
    g[i + 1] = now.pre + (int)sta.size();
  }
  return g;
}

struct state_pre {
  int pos, tag;
};

std::vector<int> trans_pre(const std::vector<int> &a,
                           const std::vector<int> &f) {
  int n = a.size();
  std::vector<int> d(n, -INF);
  std::vector<state_pre> sta;
  for (int i = n - 1; i >= 0; --i) {
    while (!sta.empty() && a[sta.back().pos] < a[i]) {
      auto t = sta.back();
      sta.pop_back();
      if (!sta.empty()) {
        sta.back().tag = std::max(sta.back().tag, t.tag);
      }
      d[t.pos] = std::max(d[t.pos], t.tag - (int)sta.size());
    }
    sta.emplace_back();
    sta.back().pos = i;
    sta.back().tag = f[i] + (int)sta.size();
  }
  while (!sta.empty()) {
    auto t = sta.back();
    sta.pop_back();
    if (!sta.empty()) {
      sta.back().tag = std::max(sta.back().tag, t.tag);
    }
    d[t.pos] = std::max(d[t.pos], t.tag - (int)sta.size());
  }
  std::vector<int> g(n + 1, -INF);
  for (int i = 0; i < n; ++i) {
    g[i + 1] = std::max(g[i], d[i]);
  }
  return g;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    --a[i];
  }

  int ans = -INF;
  for (int q = 0; q < 2; ++q) {
    std::rotate(a.begin(), std::find(a.begin(), a.end(), n - 1) + 1, a.end());
    std::vector<int> f(n + 1);
    for (int k = 0; k < m; ++k) {
      auto g_suf = trans_suf(a, f);
      auto g_pre = trans_pre(a, f);
      for (int i = 0; i <= n; ++i) {
        f[i] = std::max(g_pre[i], g_suf[i]);
      }
    }
    ans = std::max(ans, f[n]);
    std::reverse(a.begin(), a.end());
  }
  std::cout << ans << "\n";
}
