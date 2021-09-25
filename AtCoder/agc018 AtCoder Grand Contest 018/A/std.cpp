#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    int g = 0, max = 0;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        g = std::__gcd(g, v);
        max = std::max(max, v);
    }
    if (k % g == 0 && k <= max) {
        std::cout << "POSSIBLE\n";
    } else {
        std::cout << "IMPOSSIBLE\n";
    }
}
