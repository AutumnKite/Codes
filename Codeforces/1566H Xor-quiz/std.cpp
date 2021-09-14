#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> mu(n + 1);
    for (int i = 1; i <= n; ++i) {
        mu[i] += (i == 1);
        for (int j = i + i; j <= n; j += i) {
            mu[j] -= mu[i];
        }
    }

    std::vector<int> p;
    for (int i = 1; i <= n; ++i) {
        if (mu[i]) {
            p.push_back(i);
        }
    }
    std::cout << p.size();
    for (int x : p) {
        std::cout << " " << x;
    }
    std::cout << std::endl;

    std::vector<int> f(n + 1);
    for (int x : p) {
        std::cin >> f[x];
    }
    std::vector<int> 
}
