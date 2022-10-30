#include <bits/stdc++.h>

std::mt19937 rnd(std::chrono::system_clock::
                 now().time_since_epoch().count());

class bitset {
  std::vector<unsigned long long> a;

public:
  bitset(std::size_t n) : a((n + 63) / 64) {}

  bitset &operator&=(const bitset &rhs) {
    for (std::size_t i = 0; i < a.size(); ++i) {
      a[i] &= rhs.a[i];
    }
    return *this;
  }

  void set() {
    for (std::size_t i = 0; i < a.size(); ++i) {
      a[i] = ~0ull;
    }
  }

  void set(std::size_t x) {
    a[x >> 6] |= 1ull << (x & 63);
  }

  bool get(std::size_t x) {
    return a[x >> 6] & (1ull << (x & 63));
  }
};

int main() {
  int test, old, lim;
  std::cin >> test >> old >> lim;

  std::string name = "friends" + std::to_string(test);
  std::ifstream input(name + ".in");

  int n, m;
  input >> n >> m;
  std::vector<std::vector<int>> E(n, std::vector<int>(n));
  std::vector<bitset> adj(n, bitset(n));
  std::vector<std::vector<int>> A;
  for (int i = 0; i < m; ++i) {
    int u, v;
    input >> u >> v;
    --u, --v;
    E[u][v] = E[v][u] = 1;
    adj[u].set(v);
    adj[v].set(u);
    if (!old) {
      A.push_back({u, v});
    }
  }

  if (old) {
    std::ifstream old_out(name + ".out");
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        E[i][j] = 0;
      }
    }
    int c;
    old_out >> c;
    A.resize(c);
    for (int i = 0; i < c; ++i) {
      int k;
      old_out >> k;
      A[i].resize(k);
      for (int &x : A[i]) {
        old_out >> x;
        --x;
      }
      for (int x : A[i]) {
        for (int y : A[i]) {
          if (x != y) {
            ++E[x][y];
          }
        }
      }
    }
  }

  std::vector<int> p;
  for (int test = 1; test <= lim; ++test) {
    if (rnd() & 1) {
      std::shuffle(A.begin(), A.end(), rnd);
    } else {
      std::sort(A.begin(), A.end(), [&](const auto &a, const auto &b) {
        return a.size() < b.size();
      });
    }
    for (auto &C : A) {
      bitset S(n);
      S.set();
      for (int x : C) {
        S &= adj[x];
      }
      for (int i = 0; i < n; ++i) {
        if (S.get(i)) {
          p.push_back(i);
        }
      }
      std::shuffle(p.begin(), p.end(), rnd);
      for (int x : p) {
        if (S.get(x)) {
          for (int y : C) {
            ++E[x][y], ++E[y][x];
          }
          C.push_back(x);
          S &= adj[x];
        }
      }
      p.clear();
    }
    if (rnd() & 1) {
      std::shuffle(A.begin(), A.end(), rnd);
    } else {
      std::sort(A.begin(), A.end(), [&](const auto &a, const auto &b) {
        return a.size() < b.size();
      });
    }
    std::vector<std::vector<int>> B;
    for (auto &C : A) {
      bool ok = true;
      for (int x : C) {
        for (int y : C) {
          if (x != y && E[x][y] == 1) {
            ok = false;
            break;
          }
        }
        if (!ok) {
          break;
        }
      }
      if (!ok) {
        B.emplace_back(std::move(C));
      } else {
        for (int x : C) {
          for (int y : C) {
            if (x != y) {
              --E[x][y];
            }
          }
        }
      }
    }
    A.swap(B);
    for (auto &C : A) {
      std::shuffle(C.begin(), C.end(), rnd);
      std::vector<bool> vis(C.size());
      for (std::size_t i = 0; i < C.size(); ++i) {
        bool ok = true;
        for (std::size_t j = 0; j < C.size(); ++j) {
          if (!vis[j] && i != j && E[C[i]][C[j]] == 1) {
            ok = false;
            break;
          }
        }
        if (ok) {
          vis[i] = true;
          for (std::size_t j = 0; j < C.size(); ++j) {
            if (!vis[j] && i != j) {
              --E[C[i]][C[j]];
              --E[C[j]][C[i]];
            }
          }
        }
      }
      std::vector<int> tmp;
      for (std::size_t i = 0; i < C.size(); ++i) {
        if (!vis[i]) {
          tmp.push_back(C[i]);
        }
      }
      C.swap(tmp);
    }
    if (test % 1000 == 0) {
      std::cerr << test << " " << A.size() << "\n";
    }
  }

  std::ofstream output(name + ".out");
  output << A.size() << "\n";
  for (const auto &C : A) {
    output << C.size();
    for (int x : C) {
      output << " " << x + 1;
    }
    output << "\n";
  }
}
