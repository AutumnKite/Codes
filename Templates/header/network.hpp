#ifndef MYH_NETWORK_HPP
#define MYH_NETWORK_HPP 1

#include <cstdlib>
#include <algorithm>
#include <limits>
#include <vector>

namespace myh {

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

template<class Flow, class Cost>
class mcmf_network {
public:
  typedef std::size_t size_type;

  static constexpr Flow INF_flow = std::numeric_limits<Flow>::max();
  static constexpr Cost INF_cost = std::numeric_limits<Cost>::max();

protected:
  struct edge {
    size_type u, v;
    Flow flow;
    Cost cost;

    edge(size_type t_u, size_type t_v, Flow t_flow, Cost t_cost)
        : u(t_u), v(t_v), flow(t_flow), cost(t_cost) {}
  };

  size_type n, S, T;
  std::vector<edge> edges;
  std::vector<std::vector<size_type>> E;

  std::vector<Cost> dis;

  bool get_dis() {
    std::fill(dis.begin(), dis.end(), INF_cost);
    std::vector<bool> vis(n);
    std::vector<size_type> Q;
    dis[S] = 0;
    vis[S] = true;
    Q.push_back(S);
    for (size_type i = 0; i < Q.size(); ++i) {
      size_type u = Q[i];
      vis[u] = false;
      for (auto id : E[u]) {
        size_type v = edges[id].v;
        Flow flow = edges[id].flow;
        Cost cost = edges[id].cost;
        if (flow && dis[u] + cost < dis[v]) {
          dis[v] = dis[u] + cost;
          vis[v] = true;
          Q.push_back(v);
        }
      }
    }
    return dis[T] < INF_cost;
  }

  std::vector<size_type> iter;
  std::vector<bool> vis;

  Flow dfs(size_type u, Flow all) {
    if (u == T || !all) {
      return all;
    }
    vis[u] = true;
    Flow res = 0;
    for (size_type &i = iter[u]; i < E[u].size(); ++i) {
      size_type id = E[u][i];
      size_type v = edges[id].v;
      Flow flow = edges[id].flow;
      Cost cost = edges[id].cost;
      if (!vis[v] && dis[v] == dis[u] + cost) {
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
    vis[u] = false;
    if (!res) {
      dis[u] = INF_cost;
    }
    return res;
  }

public:
  mcmf_network(size_type t_n) : n(t_n), E(n), dis(n), iter(n), vis(n) {}

  void add_edge(size_type u, size_type v, Flow cap, Cost cost) {
    E[u].push_back(edges.size()), edges.emplace_back(u, v, cap, cost);
    E[v].push_back(edges.size()), edges.emplace_back(v, u, 0, -cost);
  }

  size_type edge_size() const {
    return edges.size() >> 1;
  }

  void slope(size_type t_S, size_type t_T, Flow &flow, Cost &cost) {
    std::fill(vis.begin(), vis.end(), false);
    S = t_S, T = t_T;
    flow = 0;
    cost = 0;
    while (get_dis()) {
      std::fill(iter.begin(), iter.end(), 0);
      Flow tmp = dfs(S, INF_flow);
      flow += tmp;
      cost += tmp * dis[T];
    }
  }

  Flow edge_flow(size_type id) const {
    return edges[id << 1 | 1].flow;
  }
};

} // namespace myh

#endif // MYH_NETWORK_HPP
