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

template<class Flow>
class lu_mf_network {
public:
  typedef std::size_t size_type;

  static constexpr Flow INF_flow = std::numeric_limits<Flow>::max();

protected:
  struct edge {
    size_type u, v;
    Flow lower, upper;

    edge(size_type t_u, size_type t_v, Flow t_lower, Flow t_upper)
        : u(t_u), v(t_v), lower(t_lower), upper(t_upper) {}
  };

  size_type n, S, T;
  std::vector<edge> edges;
  mf_network<Flow> G;

public:
  lu_mf_network(size_type t_n) : n(t_n), S(n), T(n + 1), G(n + 2) {}

  void add_edge(size_type u, size_type v, Flow lower, Flow upper) {
    edges.emplace_back(u, v, lower, upper);
    G.add_edge(u, v, upper - lower);
  }

  size_type edge_size() const {
    return edges.size();
  }

  bool slope() {
    std::vector<Flow> d(n);
    for (const auto &e : edges) {
      d[e.u] += e.lower;
      d[e.v] -= e.lower;
    }
    size_type S = n, T = n + 1;
    for (size_type i = 0; i < n; ++i) {
      if (d[i] < 0) {
        G.add_edge(S, i, -d[i]);
      } else if (d[i] > 0) {
        G.add_edge(i, T, d[i]);
      }
    }
    Flow flow;
    G.slope(S, T, flow);
    size_type idx = edges.size();
    for (size_type i = 0; i < n; ++i) {
      if (d[i] < 0) {
        if (G.edge_flow(idx) < -d[i]) {
          return false;
        }
        ++idx;
      } else if (d[i] > 0) {
        if (G.edge_flow(idx) < d[i]) {
          return false;
        }
        ++idx;
      }
    }
    return true;
  }

  Flow edge_flow(size_type id) const {
    return edges[id].lower + G.edge_flow(id);
  }
};

template<class Flow>
class lu_st_mf_network {
public:
  typedef std::size_t size_type;

  static constexpr Flow INF_flow = std::numeric_limits<Flow>::max();

protected:
  lu_mf_network<Flow> G;
  bool sloped;

public:
  lu_st_mf_network(size_type n) : G(n), sloped(false) {}

  void add_edge(size_type u, size_type v, Flow lower, Flow upper) {
    G.add_edge(u, v, lower, upper);
  }

  size_type edge_size() const {
    return G.edge_size() - sloped;
  }

  bool slope(size_type S, size_type T, Flow &flow) {
    sloped = true;
    G.add_edge(T, S, 0, INF_flow);
    if (!G.slope()) {
      flow = 0;
      return false;
    } else {
      flow = G.edge_flow(edge_size());
      return true;
    }
  }

  Flow edge_flow(size_type id) const {
    return G.edge_flow(id);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> b[i];
  }
  std::vector<int> deg(n);
  lu_st_mf_network<int> G(n + 2);
  std::vector<std::pair<int, int>> edge;
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    ++deg[u], --deg[v];
    edge.emplace_back(u, v);
    G.add_edge(u, v, 0, 1);
  }
  int S = n, T = n + 1;
  for (int i = 0; i < n; ++i) {
    if (!a[i]) {
      G.add_edge(S, i, 0, G.INF_flow);
      G.add_edge(i, T, 0, G.INF_flow);
    } else {
      int d = deg[i] - b[i];
      if (d & 1) {
        std::cout << "NO\n";
        return 0;
      }
      d /= 2;
      if (d > 0) {
        G.add_edge(S, i, d, d);
      } else {
        G.add_edge(i, T, -d, -d);
      }
    }
  }
  int flow;
  if (!G.slope(S, T, flow)) {
    std::cout << "NO\n";
    return 0;
  }
  std::cout << "YES\n";
  for (int i = 0; i < m; ++i) {
    int u = edge[i].first, v = edge[i].second;
    if (G.edge_flow(i)) {
      std::cout << u + 1 << " " << v + 1 << "\n";
    } else {
      std::cout << v + 1 << " " << u + 1 << "\n";
    }
  }
}
