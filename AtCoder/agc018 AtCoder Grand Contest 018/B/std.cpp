#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
            --a[i][j];
        }
    }
    std::vector<bool> vis(m, true);
    int ans = n;
    for (int k = 0; k < m; ++k) {
        std::vector<int> cnt(m);
        for (int i = 0; i < n; ++i) {
            int p = 0;
            while (!vis[a[i][p]]) {
                ++p;
            }
            ++cnt[a[i][p]];
        }
        int id = std::max_element(cnt.begin(), cnt.end()) - cnt.begin();
        ans = std::min(ans, cnt[id]);
        vis[id] = false;
    }
    std::cout << ans << "\n";
}
