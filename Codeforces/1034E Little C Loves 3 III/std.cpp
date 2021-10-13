#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    char c;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> c;
        a[i] = c - '0';
    }
    
}
