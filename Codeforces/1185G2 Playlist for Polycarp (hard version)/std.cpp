#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, T;
    std::cin >> n >> T;
    std::vector<int> a[3];
    for (int i = 0; i < n; ++i) {
        int t, b;
        std::cin >> t >> b;
        --b;
        a[b].push_back(t);
    }

}
