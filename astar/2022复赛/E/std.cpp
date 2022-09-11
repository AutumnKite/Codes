#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P, "P must be a positive integer");

  using mint = modint<P>;

protected:
  unsigned v;

public:
  modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  modint(T t_v) : v() {
    long long tmp = t_v % static_cast<long long>(P);
    if (tmp < 0) {
      tmp += P;
    }
    v = tmp;
  }

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_unsigned<T>::value,
                                   bool>::type = true>
  modint(T t_v) : v() {
    v = t_v % P;
  }

  unsigned val() const {
    return v;
  }

  static unsigned mod() {
    return P;
  }

  static mint raw(unsigned v) {
    mint res;
    res.v = v;
    return res;
  }

  mint &operator+=(const mint &rhs) {
    v < P - rhs.v ? v += rhs.v : v -= P - rhs.v;
    return *this;
  }

  mint &operator++() {
    v + 1 < P ? ++v : v = 0;
    return *this;
  }

  mint operator++(int) {
    mint tmp = *this;
    v + 1 < P ? ++v : v = 0;
    return tmp;
  }

  mint &operator-=(const mint &rhs) {
    v < rhs.v ? v += P - rhs.v : v -= rhs.v;
    return *this;
  }

  mint &operator--() {
    v ? --v : v = P - 1;
    return *this;
  }
  
  mint operator--(int) {
    mint tmp = *this;
    v ? --v : v = P - 1;
    return tmp;
  }

  mint operator-() const {
    mint res;
    res.v = v ? P - v : 0;
    return res;
  }

  mint &operator*=(const mint &rhs) {
    v = static_cast<unsigned long long>(v) * rhs.v % P;
    return *this;
  }

  mint pow(unsigned long long b) const {
    mint a(*this), s(1);
    for (; b; b >>= 1) {
      if (b & 1) {
        s *= a;
      }
      a *= a;
    }
    return s;
  }

  mint inv() const {
    return pow(P - 2);
  }

  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }

  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }

  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }

  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs.v == rhs.v;
  }

  friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs.v != rhs.v;
  }

  friend std::istream &operator>>(std::istream &in, mint &x) {
    return in >> x.v;
  }

  friend std::ostream &operator<<(std::ostream &out, const mint &x) {
    return out << x.v;
  }
};

using mint = modint<1000000007>;

const int C = 10;

class ACautomaton {
public:
  int cnt, rt;
  std::vector<std::vector<int>> trans;
  std::vector<int> fail, end;

  int new_node() {
    trans.emplace_back(C, -1);
    fail.push_back(-1);
    end.push_back(0);
    return cnt++;
  }

  ACautomaton() : cnt(), rt() {
    rt = new_node();
  }

  void insert(const std::string &s) {
    int u = rt;
    for (char c : s) {
      int v = trans[u][c - '0'];
      if (v == -1) {
        v = new_node();
        trans[u][c - '0'] = v;
      }
      u = v;
    }
    end[u] = 1;
  }

  void build() {
    std::vector<int> Q;
    fail[rt] = -1;
    for (int &v : trans[rt]) {
      if (v != -1) {
        fail[v] = rt;
        Q.push_back(v);
      } else {
        v = rt;
      }
    }
    for (int k = 0; k < (int)Q.size(); ++k) {
      int u = Q[k];
      if (fail[u] != -1) {
        end[u] |= end[fail[u]];
      }
      for (int i = 0; i < C; ++i) {
        int &v = trans[u][i];
        if (v != -1) {
          fail[v] = trans[fail[u]][i];
          Q.push_back(v);
        } else {
          v = trans[fail[u]][i];
        }
      }
    }
  }
};

std::vector<mint> BM(const std::vector<mint> &x) {
	std::vector<mint> lst(1), cur(1);
	lst[0] = cur[0] = 1;
	int lp = 0;
  mint lt = 0;
	for (int i = 0; i < (int)x.size(); ++i) {
		mint t = 0;
		for (int j = 0; j < (int)cur.size(); ++j) {
			t += x[i - j] * cur[j];
		}
		if (!t.val()) {
			continue;
		}
		if ((int)cur.size() == 1) {
			cur.resize(i + 2), lp = i, lt = t;
			continue;
		}
		mint tmp = -t * lt.inv();
		std::vector<mint> c(i - lp);
		for (mint v : lst) {
			c.push_back(v * tmp);
		}
		if (c.size() < cur.size()) {
			c.resize(cur.size());
		} else {
			lst = cur, lp = i, lt = t;
		}
		for (int j = 0; j < (int)cur.size(); ++j) {
			c[j] += cur[j];
		}
		cur = c;
	}
	return cur;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<mint> phi(n + 1);
  for (int i = 1; i <= n; ++i) {
    phi[i] += i;
    for (int j = i + i; j <= n; j += i) {
      phi[j] -= phi[i];
    }
  }
  std::vector<std::string> s(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> s[i];
  }
  std::sort(s.begin(), s.end(), [&](std::string a, std::string b) {
    return a.size() < b.size();
  });
  int l = 1;
  std::vector<mint> ans(n + 1);
  for (int k = 0; k <= m; ++k) {
    int r = k == m ? n + 1 : s[k].size();
    if (l == r) {
      continue;
    }
    ACautomaton A;
    for (int i = 0; i < k; ++i) {
      A.insert(s[i]);
    }
    A.build();
    std::vector<mint> H(r);
    for (int s = 0; s < A.cnt; ++s) {
      if (!A.end[s]) {
        std::vector<mint> f(A.cnt);
        f[s] = 1;
        std::vector<mint> h(2 * A.cnt);
        for (int i = 0; i < 2 * A.cnt; ++i) {
          h[i] = f[s];
          std::vector<mint> g(A.cnt);
          for (int u = 0; u < A.cnt; ++u) {
            if (f[u].val()) {
              for (int k = 0; k < C; ++k) {
                int v = A.trans[u][k];
                if (!A.end[v]) {
                  g[v] += f[u];
                }
              }
            }
          }
          f.swap(g);
        }
        auto a = BM(h);
        h.resize(r);
        for (int i = 2 * A.cnt; i < r; ++i) {
          for (int j = 1; j < (int)a.size(); ++j) {
            h[i] -= h[i - j] * a[j];
          }
        }
        for (int i = 0; i < r; ++i) {
          H[i] += h[i];
        }
      }
    }
    mint pw = 1;
    for (int i = 1; i < r; ++i) {
      pw *= 10;
      H[i] = pw - H[i];
      for (int j = i; j < r; j += i) {
        if (j >= l) {
          ans[j] += H[i] * phi[j / i];
        }
      }
    }
    l = r;
  }
  for (int i = 1; i <= n; ++i) {
    std::cout << ans[i] * mint(i).inv() << " \n"[i == n];
  }
}
