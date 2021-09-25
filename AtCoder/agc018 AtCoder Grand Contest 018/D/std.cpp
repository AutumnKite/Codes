#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int>>> E(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        E[u].emplace_back(v, w);
        E[v].emplace_back(u, w);
    }

    std::vector<int> size(n);
    int root = 0;

    auto dfs = [&](auto &self, int u, int fa) -> void {
        size[u] = 1;
        bool ok = true;
        for (auto [v, w] : E[u]) {
            if (v != fa) {
                self(self, v, u);
                size[u] += size[v];
                ok &= size[v] <= n / 2;
            }
        }
        ok &= n - size[u] <= n / 2;
        if (ok) {
            root = u;
        }
    };

    dfs(dfs, 0, -1);
    
    std::vector<long long> dis(n);

    auto redfs = [&](auto &self, int u, int fa) -> void {
        size[u] = 1;
        for (auto [v, w] : E[u]) {
            if (v != fa) {
                dis[v] = dis[u] + w;
                self(self, v, u);
                size[u] += size[v];
            }
        }
    };

    redfs(redfs, root, -1);

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += 2 * dis[i];
    }

    int mn = 1e9;
    for (auto [v, w] : E[root]) {
        if (size[v] * 2 == n) {
            std::cout << sum - w << "\n";
            return 0;
        }
        mn = std::min(mn, w);
    }
    std::cout << sum - mn << "\n";
}
