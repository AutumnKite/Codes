#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        if (i + a[i] < n) {
            a[i] += a[i + a[i]];
        }
    }
    std::cout << *std::max_element(a.begin(), a.end()) << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
}
