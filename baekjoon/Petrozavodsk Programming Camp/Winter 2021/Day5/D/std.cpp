#include <bits/stdc++.h>

template <class Flow>
class mf_network {
public:
  typedef std::size_t size_type;

  static const Flow INF_flow = std::numeric_limits<Flow>::max();

protected:
  struct edge {
    size_type u, v;
    Flow flow;

    edge(size_type t_u, size_type t_v, Flow t_flow)
    : u(t_u), v(t_v), flow(t_flow) {}
  };

  static const size_type npos = static_cast<size_type>(-1);

  size_type n, S, T;
  std::vector<edge> edges;
  std::vector<std::vector<size_type>> E;

  std::vector<size_type> dep;

  bool bfs() {
    std::fill(dep.begin(), dep.end(), npos);
    std::vector<size_type> Q;
    dep[S] = 0;
    Q.push_back(S);
    if (S == T) {
      return true;
    }
    for (size_type i = 0; i < Q.size(); ++i) {
      size_type u = Q[i];
      for (size_type id : E[u]) {
        size_type v = edges[id].v;
        Flow flow = edges[id].flow;
        if (flow && dep[v] == npos) {
          dep[v] = dep[u] + 1;
          Q.push_back(v);
          if (v == T) {
            return true;
          }
        }
      }
    }
    return false;
  }

  std::vector<size_type> iter;

  Flow dfs(size_type u, Flow all) {
    if (u == T || !all) {
      return all;
    }
    Flow res = 0;
    for (size_type &i = iter[u]; i < E[u].size(); ++i) {
      size_type id = E[u][i];
      size_type v = edges[id].v;
      Flow flow = edges[id].flow;
      if (dep[v] == dep[u] + 1) {
        Flow tmp = dfs(v, std::min(all, flow));
        if (tmp) {
          edges[id].flow -= tmp, edges[id ^ 1].flow += tmp;
          res += tmp, all -= tmp;
          if (!all) {
            break;
          }
        }
      }
    }
    if (!res) {
      dep[u] = npos;
    }
    return res;
  }

public:
  mf_network(size_type t_n) : n(t_n), E(n), dep(n), iter(n) {}

  void add_edge(size_type u, size_type v, Flow c) {
    E[u].push_back(edges.size()), edges.emplace_back(u, v, c);
    E[v].push_back(edges.size()), edges.emplace_back(v, u, 0);
  }

  size_type edge_size() {
    return edges.size() >> 1;
  }

  void slope(size_type t_S, size_type t_T, Flow &flow) {
    S = t_S, T = t_T;
    flow = 0;
    while (bfs()) {
      std::fill(iter.begin(), iter.end(), 0);
      flow += dfs(S, INF_flow);
    }
  }

  Flow edge_flow(size_type id) {
    return edges[id << 1 | 1].flow;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n;
  std::cin >> n;
  int L = std::min(200ll, n / 2);
  mf_network<int> G(2 * L + 2);
  int S = 2 * L, T = 2 * L + 1;
  int flow = 0;
  std::vector<bool> b(L + 1);
  b[0] = true;
  for (int k = 1; k <= L; ++k) {
    G.add_edge(S, k - 1, 1);
    G.add_edge(L + k - 1, T, 1);
    for (int i = 1; i < k; ++i) {
      if ((n - i + 1) % k == 0) {
        G.add_edge(k - 1, L + i - 1, 1);
      }
      if ((n - k + 1) % i == 0) {
        G.add_edge(i - 1, L + k - 1, 1);
      }
    }
    if ((n - k + 1) % k == 0) {
      G.add_edge(k - 1, L + k - 1, 1);
    }
    int delta;
    G.slope(S, T, delta);
    flow += delta;
    b[k] = flow == k;
  }

  std::vector<long long> ans(1, 0);
  for (int i = 0; i <= L; ++i) {
    if (b[i]) {
      ans.push_back(0);
    } else {
      ++ans.back();
    }
  }
  ans.back() += std::max(0ll, n + 1 - 2 * (L + 1));
  for (int i = L - (L * 2 == n); i >= 0; --i) {
    if (b[i]) {
      ans.push_back(0);
    } else {
      ++ans.back();
    }
  }

  std::vector<std::vector<int>> oper;
  std::vector<int> pw(1, 0);
  oper.push_back({0, 0});
  pw.push_back(2);
  for (int i = 2; i < 60; ++i) {
    oper.push_back({i, i});
    pw.push_back(i + 1);
  }
  oper.push_back({});
  for (int i = 0; i < (int)ans.size(); ++i) {
    if (i > 0) {
      oper.back().push_back(1);
    }
    for (int j = 0; j < 60; ++j) {
      if (ans[i] >> j & 1) {
        oper.back().push_back(pw[j]);
      }
    }
  }
  std::cout << oper.size() + 1 << "\n";
  for (auto v : oper) {
    std::cout << v.size();
    for (int x : v) {
      std::cout << " " << x;
    }
    std::cout << "\n";
  }
}
