#include <bits/stdc++.h>

template<typename T>
struct matrix {
    static const T INF = std::numeric_limits<T>::max() / 2;
    
    T a[2][2];

    matrix() : a{INF, INF, INF, INF} {}

    T *operator[](int x) {
        return a[x];
    }

    const T *operator[](int x) const {
        return a[x];
    }

    matrix operator*(const matrix &rhs) const {
        matrix res;
        for (int i = 0; i < 2; ++i) {
            for (int k = 0; k < 2; ++k) {
                for (int j = 0; j < 2; ++j) {
                    res.a[i][j] = std::min(res.a[i][j], a[i][k] + rhs.a[k][j]);
                }
            }
        }
        return res;
    }
};

using matll = matrix<long long>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<std::vector<std::tuple<int, long long, long long>>> E(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w1, w2;
        std::cin >> u >> v >> w1 >> w2;
        E[u].emplace_back(v, w1, w2);
        E[v].emplace_back(u, w1, w2);
    }
    
}
