#include <bits/stdc++.h>

std::mt19937_64 rnd(time(0));

struct operation {
  int l, r, x, ans, sum;

  operation(int i, int x) : l(i), r(i), x(x), ans(-1), sum() {}

  operation(int l, int r, int x) : l(l), r(r), x(x), ans(1), sum() {}
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  auto val = a;
  std::vector<operation> Q;
  for (int i = 0; i < q; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int i, x;
      std::cin >> i >> x;
      --i;
      Q.emplace_back(i, x);
      val.push_back(x);
    } else {
      int l, r, x;
      std::cin >> l >> r >> x;
      --l;
      Q.emplace_back(l, r, x);
    }
  }
  std::sort(val.begin(), val.end());
  val.erase(std::unique(val.begin(), val.end()), val.end());
  int m = val.size();
  std::vector<int> cnt(m);
  for (int i = 0; i < n; ++i) {
    a[i] = std::lower_bound(val.begin(), val.end(), a[i]) - val.begin();
    ++cnt[a[i]];
  }
  for (int i = 0; i < q; ++i) {
    if (Q[i].l == Q[i].r) {
      Q[i].x = std::lower_bound(val.begin(), val.end(), Q[i].x) - val.begin();
      ++cnt[Q[i].x];
    }
  }

  int B = sqrt(n), C = (n - 1) / B + 1;
  std::vector<int> L(C), R(C);
  for (int i = 0; i < C; ++i) {
    L[i] = i * B;
    R[i] = std::min((i + 1) * B, n);
  }

  for (int k = 2; k <= B; ++k) {
    long long pw = 1;
    while (pw < (1 << 30)) {
      pw *= k;
      std::vector<int> rd(m);
      for (int i = 0; i < m; ++i) {
        rd[i] = rnd() % k;
      }
      std::vector<int> w(n), sum(C);
      for (int i = 0; i < n; ++i) {
        w[i] = rd[a[i]];
        sum[i / B] += w[i];
      }
      for (auto &[l, r, x, ans, tmp] : Q) {
        if (l == r) {
          sum[l / B] += rd[x] - w[l];
          w[l] = rd[x];
        } else if (x == k) {
          long long tot = 0;
          int bl = l / B, br = (r - 1) / B;
          if (bl == br) {
            for (int j = l; j < r; ++j) {
              tot += w[j];
            }
          } else {
            for (int j = l; j < R[bl]; ++j) {
              tot += w[j];
            }
            for (int j = L[br]; j < r; ++j) {
              tot += w[j];
            }
            for (int j = bl + 1; j < br; ++j) {
              tot += sum[j];
            }
          }
          ans &= tot % k == 0;
          tmp = r - l;
        }
      }
    }
  }

  for (int k = 0; k < m; ++k) {
    if (cnt[k] > B) {
      std::vector<int> w(n);
      std::vector<int> pre(n), preb(C);
      for (int i = 0; i < n; ++i) {
        if (a[i] == k) {
          w[i] = 1;
          ++pre[i];
          ++preb[i / B];
        }
      }
      for (int i = 0; i < n; ++i) {
        if (i % B) {
          pre[i] += pre[i - 1];
        }
      }
      for (int i = 1; i < C; ++i) {
        preb[i] += preb[i - 1];
      }

      auto query = [&](int r) {
        int res = 0;
        if (r) {
          res += pre[r - 1];
        }
        if (r >= B) {
          res += preb[r / B - 1];
        }
        return res;
      };
  
      for (auto &[l, r, x, ans, sum] : Q) {
        if (l == r) {
          int t = (x == k) - w[l];
          if (t) {
            w[l] += t;
            for (int j = l; j < R[l / B]; ++j) {
              pre[j] += t;
            }
            for (int j = l / B; j < C; ++j) {
              preb[j] += t;
            }
          }
        } else if (x > B) {
          int s = query(r) - query(l);
          ans &= s % x == 0;
          sum += s;
        }
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    if (Q[i].ans != -1) {
      Q[i].ans &= Q[i].sum == Q[i].r - Q[i].l;
      std::cout << (Q[i].ans ? "YES\n" : "NO\n");
    }
  }
}
