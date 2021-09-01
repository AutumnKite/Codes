#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    int s = 1, s1 = 1;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        s *= 3;
        if (!(x & 1)) {
            s1 *= 2;
        }
    }
    std::cout << s - s1 << "\n";
}