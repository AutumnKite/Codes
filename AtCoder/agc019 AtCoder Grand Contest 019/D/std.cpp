#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::string sa, sb;
    std::cin >> sa >> sb;
    int n = sa.size();
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = sa[i] - '0';
        b[i] = sb[i] - '0';
    }

    if (std::find(b.begin(), b.end(), 1) == b.end()) {
        if (std::find(a.begin(), a.end(), 1) == a.end()) {
            std::cout << 0 << "\n";
        } else {
            std::cout << -1 << "\n";
        }
        return 0;
    }

    std::vector<int> pos;
    for (int i = 0; i < n; ++i) {
        if (b[i]) {
            pos.push_back(i);
        }
    }
    int m = pos.size();

    int ans = INF;
    for (int k = 0; k < n; ++k) {
        auto t(a);
        for (int i = 0; i < n; ++i) {
            t[i] ^= b[(i + k) % n];
        }
        int sum = std::accumulate(t.begin(), t.end(), 0);
        std::vector<int> L(n), R(n);
        for (int i = 0; i < m; ++i) {
            int l = pos[i], r = pos[(i + 1) % m];
            std::vector<int> p;
            for (int x = (l + 1) % n; x != r; x = (x + 1) % n) {
                if (t[x]) {
                    p.push_back(x);
                }
            }
            if (p.empty()) {
                continue;
            }
            for (int j = 0; j < (int)p.size(); ++j) {
                int l1 = (p[j] + n - l) % n, l2 = (p[j] + n - l - 1) % n;
                int r1 = (r + n - p[j]) % n, r2 = (r + n - p[j] - 1) % n;
                L[r2] = std::max(L[r2], l1);
                R[l2] = std::max(R[l2], r1);
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            L[i] = std::max(L[i], L[i + 1]);
            R[i] = std::max(R[i], R[i + 1]);
        }
        for (int i = 0; i < n; ++i) {
            ans = std::min(ans, i * 2 + L[i] + (k + L[i]) % n + sum);
            ans = std::min(ans, i * 2 + L[i] + (n - k + n - L[i]) % n + sum);
            ans = std::min(ans, i * 2 + R[i] + (k + n - R[i]) % n + sum);
            ans = std::min(ans, i * 2 + R[i] + (n - k + R[i]) % n + sum);
        }
    }
    std::cout << ans << "\n";
}
