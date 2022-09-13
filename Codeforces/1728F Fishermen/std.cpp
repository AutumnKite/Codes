#include <bits/stdc++.h>

template<class Flow>
class mf_network {
public:
  typedef std::size_t size_type;

  static constexpr Flow INF_flow = std::numeric_limits<Flow>::max();

protected:
  struct edge {
    size_type u, v;
    Flow flow;

    edge(size_type t_u, size_type t_v, Flow t_flow)
        : u(t_u), v(t_v), flow(t_flow) {}
  };

  static constexpr size_type npos = static_cast<size_type>(-1);

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

  size_type edge_size() const {
    return edges.size() >> 1;
  }

  bool check(size_type t_S, size_type t_T) {
    S = t_S, T = t_T;
    return bfs();
  }

  void rollback(size_type last) {
    while (edge_size() > last) {
      edges.pop_back();
      edges.pop_back();
    }
    for (size_type i = 0; i < n; ++i) {
      while (!E[i].empty() && E[i].back() >= edges.size()) {
        E[i].pop_back();
      }
    }
  }

  void slope(size_type t_S, size_type t_T, Flow &flow) {
    S = t_S, T = t_T;
    flow = 0;
    while (bfs()) {
      std::fill(iter.begin(), iter.end(), 0);
      flow += dfs(S, INF_flow);
    }
  }

  Flow edge_flow(size_type id) const {
    return edges[id << 1 | 1].flow;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int &x : a) {
    std::cin >> x;
  }
  std::sort(a.begin(), a.end());
  
  auto val = a;
  val.erase(std::unique(val.begin(), val.end()), val.end());
  int m = val.size();
  
  mf_network<int> G(m + n + 2);
  int S = m + n, T = m + n + 1;
  for (int i = 0; i < m; ++i) {
    auto l = std::lower_bound(a.begin(), a.end(), val[i]);
    auto r = std::upper_bound(a.begin(), a.end(), val[i]);
    G.add_edge(i, T, r - l);
  }
  int now = 0;
  long long ans = 0;
  for (int k = 0; k < n; ++k) {
    G.add_edge(S, m + k, 1);
    std::vector<int> all(m);
    for (int i = 0; i < m; ++i) {
      all[i] = (now / val[i] + 1) * val[i];
    }
    std::sort(all.begin(), all.end());
    all.erase(std::unique(all.begin(), all.end()), all.end());
    int l = 0, r = all.size();
    while (l + 1 < r) {
      int mid = (l + r) >> 1;
      int lst = G.edge_size();
      for (int i = 0; i < m; ++i) {
        if ((now / val[i] + 1) * val[i] < all[mid]) {
          G.add_edge(m + k, i, 1);
        }
      }
      if (G.check(S, T)) {
        r = mid;
      } else {
        l = mid;
      }
      G.rollback(lst);
    }
    for (int i = 0; i < m; ++i) {
      if ((now / val[i] + 1) * val[i] == all[l]) {
        G.add_edge(m + k, i, 1);
      }
    }
    int flow;
    G.slope(S, T, flow);
    now = all[l];
    ans += now;
  }
  std::cout << ans << "\n";
}
