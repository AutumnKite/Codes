#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::string s;
    std::cin >> s;
    int n = s.size();
    int l = 0, r = n - 1;
    int ans = 0;
    while (l < r) {
        if (s[l] == s[r]) {
            ++l, --r;
        } else if (s[l] == 'x') {
            ++l;
            ++ans;
        } else if (s[r] == 'x') {
            --r;
            ++ans;
        } else {
            std::cout << -1 << "\n";
            return 0;
        }
    }
    std::cout << ans << "\n";
}