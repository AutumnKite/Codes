#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::string s;
    std::cin >> s;
    int n = s.size();
    std::map<int, int> mp;
    int now = 0;
    mp[0] = 0;
    for (int i = 0; i < n; ++i) {
        now ^= 1 << (s[i] - 'a');
        int f = mp.count(now) ? mp[now] + 1 : n;
        for (int j = 0; j < 26; ++j) {
            f = std::min(f, mp.count(now ^ 1 << j) ? mp[now ^ 1 << j] + 1 : n);
        }
        if (i == n - 1) {
            std::cout << f << "\n";
        }
        if (mp.count(now)) {
            mp[now] = std::min(mp[now], f);
        } else {
            mp[now] = f;
        }
    }
}