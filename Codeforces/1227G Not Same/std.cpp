#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].first;
        a[i].second = i;
    }
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
        std::string s(n, '0');
        for (int j = 0; j < n; ++j) {
            if (a[i].first > (j > i)) {
                --a[i].first;
                s[a[i].second] = '1';
            }
        }
    }
}
