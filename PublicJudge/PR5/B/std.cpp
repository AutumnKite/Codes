#include <bits/stdc++.h>

std::string table[] = {
  "2646542750919063263921838254385335359296",
  "95333687409799371738385246754668326736320",
  "3536350769544296768242436302475752806856560",
  "134432093788769769071404891906890311935615056",
  "5255445602020024722712116211506774729468563184",
  "210302379850964483238163085628089110159782496200",
  "8639747663671245968893005729141383394728062673280",
  "363034112114677725911711960294923695984623345346624"
};

using bint = __uint128_t;

std::ostream &operator<<(std::ostream &out, bint x) {
  std::string s;
  while (s.empty() || x) {
    s.push_back(x % 10 + '0');
    x /= 10;
  }
  std::reverse(s.begin(), s.end());
  return out << s;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  if (n > 34) {
    std::cout << table[n - 35] << "\n";
    return 0;
  }

  bint fac = 1;
  for (int i = 1; i <= n; ++i) {
    fac *= i;
  }
  
  std::vector<bool> vis(n);
  bint ans = 0;

  auto dfs = [&](auto &self, int k, int d, int sz, bint ways) -> void {
    if (k == n) {
      ans += ways / sz - ways / n;
      return;
    }
    int p = (k + d) % n;
    if (!vis[p]) {
      vis[p] = true;
      self(self, k + 1, p, sz + 1, ways / sz);
      vis[p] = false;
    }
    bool ex = vis[p];
    vis[p] = true;
    self(self, k + 1, d, sz + !ex, ways);
    vis[p] = ex;
  };

  vis[0] = true;
  dfs(dfs, 1, 0, 1, fac);
  std::cout << ans << "\n";
}
