#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &x : a) {
        std::cin >> x;
    }
    std::sort(a.begin(), a.end());
    std::string s;
    std::cin >> s;

    auto flip = [&](char c) {
        return c == 'L' ? 'R' : 'L';
    };

    for (int i = 0, j = 0; i < n; i = j) {
        j = i;
        while (j < n && s[j] == s[i]) {
            ++j;
        }
        std::reverse(a.begin() + i + 1, a.begin() + j);
        for (int k = i; k < j; ++k) {
            std::cout << a[k] << " " << (k == i || (k - i) & 1 ? s[i] : flip(s[i])) << "\n";
        }
    }
}
