#include <bits/stdc++.h>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    int n;
    std::cin >> n;
    std::vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> b[i];
    }
    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin(), id.end(), [&](int x, int y) {
      return b[x] > b[y];
    });
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
      a[i] = b[id[i]];
    }
    long long p, q;
    std::cin >> p >> q;

    std::vector<long long> sum(n + 1);
    for (int i = 0; i < n; ++i) {
      sum[i + 1] = sum[i] + a[i];
    }

    std::vector<int> len(n);
    int max = 0;
    for (int i = 0; i < n; ++i) {
      int l = i + 1, r = n + 1;
      while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (q * (mid - i) * a[i] <= p * (sum[mid] - sum[i])) {
          l = mid;
        } else {
          r = mid;
        }
      }
      len[i] = l - i;
      max = std::max(max, len[i]);
    }

    std::vector<int> d(n + 1);
    for (int i = 0; i + max <= n; ++i) {
      if (len[i] < max) {
        continue;
      }
      long long v = q * max * a[i] - p * (sum[i + max - 1] - sum[i]);
      int l = i + max, r = n + 1;
      while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (p * a[mid - 1] >= v) {
          l = mid;
        } else {
          r = mid;
        }
      }
      ++d[i], --d[l];
    }
    for (int i = 1; i < n; ++i) {
      d[i] += d[i - 1];
    }

    std::vector<int> ans;
    for (int i = 0; i < n; ++i) {
      if (!d[i]) {
        ans.push_back(id[i]);
      }
    }
    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << "\n";
    std::string sep;
    for (int x : ans) {
      std::cout << sep << x + 1;
      sep = " ";
    }
    std::cout << "\n";
  }
}
