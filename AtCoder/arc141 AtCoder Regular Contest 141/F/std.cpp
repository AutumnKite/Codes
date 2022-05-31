#include <bits/stdc++.h>

const int C = 4;

class ACautomaton {
  int cnt, rt;
  std::vector<std::vector<int>> trans;
  std::vector<int> fail;
  std::vector<int> len, size, id, lst;

  int new_node(int l) {
    trans.emplace_back(C, -1);
    fail.push_back(-1);
    len.push_back(l);
    size.push_back(0);
    id.push_back(-1);
    lst.push_back(-1);
    return cnt++;
  }

public:
  ACautomaton() : cnt(), rt() {
    rt = new_node(0);
  }

  void insert(const std::string &s, int x) {
    int u = rt;
    ++size[u], id[u] = x;
    for (char c : s) {
      int v = trans[u][c - 'A'];
      if (v == -1) {
        v = new_node(len[u] + 1);
        trans[u][c - 'A'] = v;
      }
      u = v;
      ++size[u], id[u] = x;
    }
    lst[u] = u;
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
      if (lst[fail[u]] != -1) {
        lst[u] = lst[fail[u]];
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

  std::string work(const std::string &s, int x) const {
    std::vector<int> sta;
    sta.push_back(rt);
    std::string res;
    for (char c : s) {
      int u = trans[sta.back()][c - 'A'];
      sta.push_back(u);
      res.push_back(c);
      while (lst[u] != -1 && (res.size() < s.size() || lst[u] != u)) {
        for (int i = 0; i < len[lst[u]]; ++i) {
          sta.pop_back();
          res.pop_back();
        }
        u = sta.back();
      }
    }
    return res;
  }

  std::vector<std::pair<int, int>> query(const std::string &s) const {
    int u = rt;
    for (char c : s) {
      u = trans[u][c - 'A'];
    }
    std::vector<std::pair<int, int>> res(s.size(), std::make_pair(0, -1));
    for (int v = fail[u]; v != rt; v = fail[v]) {
      res[len[v]] = std::make_pair(size[v], id[v]);
    }
    return res;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::string> a(n);
  ACautomaton S;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    S.insert(a[i], i);
  }
  S.build();

  std::vector<std::string> b;
  ACautomaton T;
  for (int i = 0; i < n; ++i) {
    auto t = S.work(a[i], i);
    if (t.empty()) {
      continue;
    }
    if (t.size() < a[i].size()) {
      std::cout << "Yes\n";
      return 0;
    }
    T.insert(t, b.size());
    b.push_back(t);
  }
  T.build();
  std::vector<std::vector<std::pair<int, int>>> st;
  for (const auto &t : b) {
    st.push_back(T.query(t));
  }
  for (int i = 0; i < (int)b.size(); ++i) {
    for (int k = 1; k < (int)b[i].size(); ++k) {
      auto [c, j] = st[i][k];
      if (c > 1) {
        std::cout << "Yes\n";
        return 0;
      }
      if (c == 0) {
        continue;
      }
      if (b[i].size() == b[j].size() && st[j][b[i].size() - k].second == i) {
        continue;
      }
      std::cout << "Yes\n";
      return 0;
    }
  }
  std::cout << "No\n";
}
