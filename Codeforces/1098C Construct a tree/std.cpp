#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long s;
    std::cin >> n >> s;

    if (s < 2 * n - 1 || s > 1ll * n * (n + 1) / 2) {
        std::cout << "No\n";
        return 0;
    }

    std::cout << "Yes\n";

    if (s == 1ll * n * (n + 1) / 2) {
        for (int i = 1; i < n; ++i) {
            std::cout << i << " ";
        }
        std::cout << "\n";
        return 0;
    }

    auto solve = [&](int d, long long t) {
        std::vector<int> p(n), dep(n);
        p[0] = -1;
        dep[0] = 1;
        for (int i = 1; i < n; ++i) {
            p[i] = (i - 1) / d;
            dep[i] = dep[p[i]] + 1;
        }

        if (!t) {
            return p;
        }

        std::vector<bool> chain(n);
        long long c = 1;
        int lst = -1;
        while (c <= n) {
            chain[c - 1] = true;
            lst = c - 1;
            c *= d;
        }

        for (int i = n - 1; i >= 0; --i) {
            if (!chain[i]) {
                int delta = dep[lst] - dep[p[i]];
                if (delta >= 
            }
        }
    };

    for (int d = 2; d < n; ++d) {
        long long m = n, t = s;
        long long c = 1;
        int dep = 1;
        while (m) {
            if (m < c) {
                t -= m * dep;
                m = 0;
            } else {
                t -= c * dep;
                m -= c;
                c *= d;
                ++dep;
            }
        }
        if (t >= 0) {
            solve(d, t);
            return 0;
        }
    }
}
