#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::string s;
    std::cin >> s;
    for (int i = 0; i + 1 < (int)s.size(); ++i) {
        if (s[i] == 'A' && s[i + 1] == 'C') {
            std::cout << "Yes\n";
            return 0;
        }
    }
    std::cout << "No\n";
}