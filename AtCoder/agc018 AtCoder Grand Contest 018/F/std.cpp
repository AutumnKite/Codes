#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    int rtA = -1, rtB = -1;
    std::vector<std::vector<int>> A(n), B(n);
    for (int i = 0; i < n; ++i) {
        int fa;
        std::cin >> fa;
        if (fa == -1) {
            rtA = i;
            continue;
        }
        --fa;
        A[fa].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        int fa;
        std::cin >> fa;
        if (fa == -1) {
            rtB = i;
            continue;
        }
        --fa;
        B[fa].push_back(i);
    }

    for (int i = 0; i < n; ++i) {
        if ((A[i].size() & 1) != (B[i].size() & 1)) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    std::vector<std::vector<int>> E(n);

    auto add_edges = [&](const std::vector<int> &id) {
        for (int i = 0; i + 1 < (int)id.size(); i += 2) {
            E[id[i]].push_back(id[i + 1]);
            E[id[i + 1]].push_back(id[i]);
        }
    };

    auto dfs = [&](auto &self, const auto &T, int u) -> std::vector<int> {
        std::vector<int> res;
        for (int v : T[u]) {
            auto tmp = self(self, T, v);
            res.insert(res.end(), tmp.begin(), tmp.end());
        }
        if (res.size() & 1) {
            return res;
        } else {
            add_edges(res);
            return {u};
        }
    };

    add_edges(dfs(dfs, A, rtA));
    add_edges(dfs(dfs, B, rtB));

    std::vector<int> col(n, -1);

    auto color = [&](auto self, int u, int c) -> void {
        if (col[u] != -1) {
            return;
        }
        col[u] = c;
        for (int v : E[u]) {
            self(self, v, c ^ 1);
        }
    };

    for (int i = 0; i < n; ++i) {
        if (!(A[i].size() & 1)) {
            color(color, i, 0);
        }
    }

    std::cout << "POSSIBLE\n";
    for (int i = 0; i < n; ++i) {
        if (A[i].size() & 1) {
            std::cout << 0 << " ";
        } else {
            std::cout << (col[i] ? 1 : -1) << " ";
        }
    }
    std::cout << "\n";
}
