#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    std::vector<int> a(q + 1), c(q + 1);
    int LG = std::__lg(q + 1) + 1;
    std::vector<std::vector<int>> fa(q + 1, std::vector<int>(LG, -1));
    std::vector<std::vector<long long>> sum(q + 1, std::vector<long long>(LG));
    std::vector<long long> sa(q + 1), sc(q + 1);
    std::cin >> a[0] >> c[0];
    sc[0] = 1ll * a[0] * c[0];
    for (int i = 1; i <= q; ++i) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int p;
            std::cin >> p;
            std::cin >> a[i] >> c[i];
            fa[i][0] = p;
            sum[i][0] = a[i];
            for (int j = 1; j < LG && fa[i][j - 1] != -1; ++j) {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
                sum[i][j] = sum[i][j - 1] + sum[fa[i][j - 1]][j - 1];
            }
            sc[i] = sc[p] + 1ll * a[i] * c[i];
            sa[i] = sa[p] + a[i];
        } else {
            int u;
            std::cin >> u;
            int w;
            std::cin >> w;
            long long tw = sa[u] - w;
            if (tw <= 0) {
                std::cout << sc[u] << "\n";
                continue;
            }
            for (int j = LG - 1; j >= 0; --j) {
                if (fa[u][j] != -1 && sum[u][j] <= tw) {
                    tw -= sum[u][j];
                    u = fa[u][j];
                }
            }
            std::cout << sc[u] - tw * c[u] << "\n";
        }
    }
}
