#include <bits/stdc++.h>

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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  std::vector<std::vector<int>> Ea(n), Eb(m);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    Ea[u].push_back(v);
    Ea[v].push_back(u);
  }
  for (int i = 0; i < m - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    Eb[u].push_back(v);
    Eb[v].push_back(u);
  }

  auto dfs = [&](auto &self, auto &E, int u, int fa, auto &id) -> void {
    if (fa != -1) {
      E[u].erase(std::find(E[u].begin(), E[u].end(), fa));
    }
    id.push_back(u);
    for (int v : E[u]) {
      self(self, E, v, u, id);
    }
  };

  std::vector<int> ida, idb;
  dfs(dfs, Ea, 0, -1, ida);
  dfs(dfs, Eb, 0, -1, idb);
  std::reverse(ida.begin(), ida.end());
  std::reverse(idb.begin(), idb.end());

  std::vector<std::vector<int>> f(n, std::vector<int>(m));
  for (int x : ida) {
    for (int y : idb) {
      for (int yv : Eb[y]) {
        f[x][y] = std::max(f[x][y], f[x][yv]);
      }
      for (int xv : Ea[x]) {
        f[x][y] = std::max(f[x][y], f[xv][y]);
      }
      if (a[x] == b[y]) {
        int ca = Ea[x].size(), cb = Eb[y].size();
        mcmf_network<int, int> G(ca + cb + 2);
        int S = ca + cb, T = ca + cb + 1;
        for (int i = 0; i < ca; ++i) {
          for (int j = 0; j < cb; ++j) {
            G.add_edge(i, ca + j, 1, -f[Ea[x][i]][Eb[y][j]]);
          }
        }
        for (int i = 0; i < ca; ++i) {
          G.add_edge(S, i, 1, 0);
        }
        for (int i = 0; i < cb; ++i) {
          G.add_edge(ca + i, T, 1, 0);
        }
        int flow, cost;
        G.slope(S, T, flow, cost);
        f[x][y] = std::max(f[x][y], -cost + 1);
      }
    }
  }
  std::cout << f[0][0] << "\n";
}
