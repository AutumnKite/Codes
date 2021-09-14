#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        v[i] = i;
    }
    for (int i = 1; i * i <= n; ++i) {
        for (int j = i * i; j <= n; j += i) {
            while (v[j] % (i * i) == 0) {
                v[j] /= i;
            }
        }
    }

    std::vector<int> p;
    for (int i = 1; i <= n; ++i) {
        if (v[i] == i) {
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
    for (int i = 2; i <= n; ++i) {
        if (v[i] == i) {
            f[i] ^= f[1];
        }
    }
    for (int i = 2; i <= n; ++i) {
        if (v[i] == i) {
            for (int j = i + i; j <= n; j += i) {
                if (v[j] == j) {
                    f[j] ^= f[i];
                }
            }
        }
    }
    for (int i = n; i >= 1; --i) {
        if (v[i] == i) {
            for (int j = i + i; j <= n; j += i) {
                if (v[j] == j) {
                    f[i] ^= f[j];
                }
            }
        }
    }
}
