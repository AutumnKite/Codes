#include <bits/stdc++.h>

class two_sat {
    int n;
    std::vector<std::vector<int>> E;

    int idx;
    std::vector<int> dfn, low;
    std::vector<int> sta;
    std::vector<bool> vis;

    int cnt;
    std::vector<int> bel;

    void tarjan(int u) {
        dfn[u] = low[u] = idx++;
        sta.push_back(u);
        vis[u] = true;
        for (int v : E[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = std::min(low[u], low[v]);
            } else if (vis[v]) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int x;
            do {
                x = sta.back();
                vis[x] = false;
                sta.pop_back();
                bel[x] = cnt;
            } while (x != u);
            ++cnt;
        }
    }

public:
    two_sat(int _n)
    : n(_n << 1), E(n), idx(0), dfn(n, -1), low(n), vis(n), cnt(0), bel(n) {}

    void add_edge(int u, bool x, int v, bool y) {
        E[u << 1 | x].push_back(v << 1 | y);
        E[v << 1 | !y].push_back(u << 1 | !x);
    }

    std::pair<bool, std::vector<int>> solve() {
        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) {
                tarjan(i);
            }
        }
        std::vector<int> ans(n >> 1);
        for (int i = 0; i < (n >> 1); ++i) {
            if (bel[i << 1] == bel[i << 1 | 1]) {
                return std::make_pair(false, ans);
            }
            ans[i] = bel[i << 1] > bel[i << 1 | 1];
        }
        return std::make_pair(true, ans);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    int idx = 0;
    std::vector<std::map<int, int>> id(n);
    
    auto insert = [&](int x, int v) {
        if (!id[x].count(v)) {
            id[x][v] = idx++;
        }
    };

    std::vector<std::pair<std::array<int, 3>, int>> constraint;

    for (int i = 0; i < m; ++i) {
        int x, y, z, v;
        std::cin >> x >> y >> z >> v;
        --x, --y, --z;
        constraint.emplace_back(std::array<int, 3>{x, y, z}, v);
        insert(x, v);
        insert(y, v);
        insert(z, v);
    }

    two_sat G(idx);

    for (int i = 0; i < n; ++i) {
        int lst = -1;
        for (auto [v, x] : id[i]) {
            if (lst != -1) {
                G.add_edge(x, 1, lst, 1);
            }
            lst = x;
        }
    }

    for (auto [x, v] : constraint) {
        std::array it = {id[x[0]].find(v), id[x[1]].find(v), id[x[2]].find(v)};
        std::array nx = {std::next(it[0]), std::next(it[1]), std::next(it[2])};
        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                G.add_edge(it[i]->second, 0, it[j]->second, 1);
                if (nx[i] != id[x[i]].end() && nx[j] != id[x[j]].end()) {
                    G.add_edge(nx[i]->second, 1, nx[j]->second, 0);
                }
            }
        }
    }

    auto [ok, st] = G.solve();

    if (!ok) {
        std::cout << "NO\n";
        return 0;
    }

    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = 1;
        for (auto [v, x] : id[i]) {
            // std::cerr << i << " " << v << " " << x << " " << st[x] << "\n";
            if (st[x]) {
                ans[i] = v;
            }
        }
    }
    std::cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " ";
    }
    std::cout << "\n";
}
