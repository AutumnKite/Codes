#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<int> cnt(26);
    for (int i = 0; i < n; ++i) {
        ++cnt[s[i] - 'a'];
    }
    long long ans = 1ll * n * (n - 1) / 2;
    for (int x : cnt) {
        ans -= 1ll * x * (x - 1) / 2;
    }
    std::cout << ans + 1 << "\n";
}
