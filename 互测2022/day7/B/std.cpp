#include <bits/stdc++.h>

// modified
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

  size_type n;
  std::vector<edge> edges;
  std::vector<std::vector<size_type>> E;

  std::vector<Cost> dis;

  bool get_dis(bool first) {
    if (first) {
      std::fill(dis.begin(), dis.end(), INF_cost);
      dis[0] = 0;
      for (size_type u = 0; u < n; ++u) {
        for (auto id : E[u]) {
          size_type v = edges[id].v;
          Flow flow = edges[id].flow;
          Cost cost = edges[id].cost;
          if (flow && dis[u] + cost < dis[v]) {
            dis[v] = dis[u] + cost;
          }
        }
      }
    } else {
      auto h = dis;
      std::fill(dis.begin(), dis.end(), INF_cost);
      std::priority_queue<std::pair<Cost, size_type>> Q;
      std::vector<bool> vis(n);
      dis[0] = 0;
      Q.emplace(0, 0);
      while (!Q.empty()) {
        auto u = Q.top().second;
        Q.pop();
        if (vis[u]) {
          continue;
        }
        vis[u] = true;
        for (auto id : E[u]) {
          size_type v = edges[id].v;
          Flow flow = edges[id].flow;
          Cost cost = edges[id].cost + h[u] - h[v];
          if (flow && dis[u] + cost < dis[v]) {
            dis[v] = dis[u] + cost;
            Q.emplace(-dis[v], v);
          }
        }
        dis[u] += h[u] - h[0];
      }
    }
    return dis[n - 1] < INF_cost;
  }

  std::vector<size_type> iter;
  std::vector<bool> vis;

  Flow dfs(size_type u, Flow all) {
    if (u == n - 1 || !all) {
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

  void slope(Flow &flow, Cost &cost) {
    std::fill(vis.begin(), vis.end(), false);
    flow = 0;
    cost = 0;
    bool first = true;
    while (get_dis(first)) {
      first = false;
      std::fill(iter.begin(), iter.end(), 0);
      Flow tmp = dfs(0, INF_flow);
      flow += tmp;
      cost += tmp * dis[n - 1];
    }
  }

  Flow edge_flow(size_type id) const {
    return edges[id << 1 | 1].flow;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;
  mcmf_network<int, long long> G(n + 2);
  for (int i = 0; i <= n; ++i) {
    G.add_edge(i, i + 1, k, 0);
  }
  for (int i = 0; i < m; ++i) {
    int l, r, v;
    std::cin >> l >> r >> v;
    --l;
    G.add_edge(l, r, 1, -v);
  }
  int flow;
  long long cost;
  G.slope(flow, cost);
  std::cout << -cost << "\n";
}
