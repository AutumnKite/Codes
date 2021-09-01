#include <bits/stdc++.h>

const int P = 1000000007;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n), pa(n), pb(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
        pa[a[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
        --b[i];
        pb[b[i]] = i;
    }

    std::vector<std::vector<int>> c(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::vector<bool> vis(n);
            for (int k = i; k < n; ++k) {
                vis[a[k]] = true;
            }
            for (int k = j; k < n; ++k) {
                c[i][j] += vis[b[k]];
            }
        }
    }

    std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 1));
    f[n][n] = 1;
    for (int k = 1; k <= n / 3; ++k) {
        std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1));
        g.swap(f);
        for (int i = n; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                g[i][j] = (g[i][j] + g[i][j + 1]) % P;
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                g[i][j] = (g[i][j] + g[i + 1][j]) % P;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (c[i][j] >= 3 * k && pa[b[j]] > i && pb[a[i]] > j) {
                    f[i][j] = 1ll * g[i + 1][j + 1] * (c[i][j] - 3 * k + 1) % P;
                }
            }
        }
    }

    int ans = f[0][0];
    for (int i = 0; i < n / 3; ++i) {
        ans = 1ll * ans * (3 * i + 1) % P;
        ans = 1ll * ans * (3 * i + 2) % P;
    }
    std::cout << ans << "\n";
}