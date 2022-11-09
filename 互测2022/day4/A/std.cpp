#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int sub;
  std::cin >> sub;
  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  
  const int B = 511, C = (n - 1) / B + 1, lg = std::__lg(B) + 1;
  std::vector<int> L(C), R(C);
  for (int i = 0; i < C; ++i) {
    L[i] = i * B, R[i] = std::min((i + 1) * B, n);
  }

  std::vector<std::vector<int>> tag(C), val(C);

  auto pushdown = [&](int c) {
    int S = tag[c].size();
    for (int i = 0; i < lg; ++i) {
      if (S >> i & 1) {
        for (int j = R[c] - 1; j >= L[c] + (1 << i); --j) {
          a[j] ^= a[j - (1 << i)];
        }
      }
    }
    auto sum = tag[c];
    std::reverse(sum.begin(), sum.end());
    sum.resize(1 << lg);
    for (int i = 0; i < lg; ++i) {
      for (int S = 0; S < (1 << lg); ++S) {
        if (S >> i & 1) {
          sum[S ^ (1 << i)] ^= sum[S];
        }
      }
    }
    for (int i = L[c]; i < R[c]; ++i) {
      a[i] ^= sum[i - L[c]];
    }
    tag[c].clear();
  };

  auto build = [&](int c) {
    std::vector<int> sum(a.begin() + L[c], a.begin() + R[c]);
    std::reverse(sum.begin(), sum.end());
    sum.resize(1 << lg);
    for (int i = 0; i < lg; ++i) {
      for (int S = 0; S < (1 << lg); ++S) {
        if (S >> i & 1) {
          sum[S] ^= sum[S ^ (1 << i)];
        }
      }
    }
    val[c] = sum;
  };

  auto query = [&](int x) {
    int c = x / B, S = tag[c].size();
    if (x == R[c] - 1) {
      return val[c][S];
    } else {
      int ans = 0;
      for (int T = S; ; T = (T - 1) & S) {
        if (x - T >= L[c]) {
          ans ^= a[x - T];
        }
        if (!T) {
          break;
        }
      }
      for (int T = x - L[c]; T < S; T = (T + 1) | (x - L[c])) {
        ans ^= tag[c][S - T - 1];
      }
      return ans;
    }
  };

  auto update = [&](int c) {
    tag[c].push_back(query(L[c] - 1));
    if ((int)tag[c].size() == B) {
      pushdown(c);
      build(c);
    }
  };

  for (int i = 0; i < C; ++i) {
    build(i);
  }

  while (q--) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r;
      std::cin >> l >> r;
      --l;
      int bl = l / B, br = (r - 1) / B;
      if (bl == br) {
        pushdown(bl);
        for (int i = r - 1; i > l; --i) {
          a[i] ^= a[i - 1];
        }
        build(bl);
        continue;
      }
      pushdown(br);
      for (int i = r - 1; i > L[br]; --i) {
        a[i] ^= a[i - 1];
      }
      a[L[br]] ^= query(L[br] - 1);
      build(br);
      for (int i = br - 1; i > bl; --i) {
        update(i);
      }
      pushdown(bl);
      for (int i = R[bl] - 1; i > l; --i) {
        a[i] ^= a[i - 1];
      }
      build(bl);
    } else {
      int x;
      std::cin >> x;
      --x;
      std::cout << query(x) << "\n";
    }
  }
  for (int i = 0; i < C; ++i) {
    pushdown(i);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << "\n";
  }
}
