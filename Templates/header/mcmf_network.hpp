#ifndef MYH_MCMF_NETWORK_HPP
#define MYH_MCMF_NETWORK_HPP 1

#include <cstdlib>
#include <algorithm>
#include <limits>
#include <vector>

namespace myh {

template <class Flow, class Cost>
class mcmf_network {
public:
  typedef std::size_t size_type;

  static const Flow INF_flow = std::numeric_limits<Flow>::max();
  static const Cost INF_cost = std::numeric_limits<Cost>::max();

protected:
  struct edge {
    size_type u, v;
    Flow flow;
    Cost cost;

    edge(size_type _u, size_type _v, Flow _flow, Cost _cost)
    : u(_u), v(_v), flow(_flow), cost(_cost) {}
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
  mcmf_network(size_type _n) : n(_n), E(_n), dis(_n), iter(_n), vis(_n) {}

  void add_edge(size_type u, size_type v, Flow cap, Cost cost) {
    E[u].push_back(edges.size()), edges.emplace_back(u, v, cap, cost);
    E[v].push_back(edges.size()), edges.emplace_back(v, u, 0, -cost);
  }

  size_type edge_size() {
    return edges.size() >> 1;
  }

  void slope(size_type _S, size_type _T, Flow &flow, Cost &cost) {
    std::fill(vis.begin(), vis.end(), false);
    S = _S, T = _T;
    flow = 0;
    cost = 0;
    while (get_dis()) {
      std::fill(iter.begin(), iter.end(), 0);
      Flow tmp = dfs(S, INF_flow);
      flow += tmp;
      cost += tmp * dis[T];
    }
  }

  Flow edge_flow(size_type id) {
    return edges[id << 1 | 1].flow;
  }
};

} // namespace myh

#endif // MYH_MCMF_NETWORK_HPP
