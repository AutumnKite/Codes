#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int a[4];
    std::cin >> a[0] >> a[1] >> a[2] >> a[3];
    int n;
    std::cin >> n;
    for (int i = 1; i < 4; ++i) {
        a[i] = std::min(a[i], a[i - 1] * 2);
    }
    std::cout << 1ll * (n / 2) * a[3] + (n % 2) * a[2] << "\n";
}
