#include <bits/stdc++.h>

class linear_basis {
    const int B;

    int cnt;
    int a[20], mask[20], bas[20];

public:
    linear_basis(int _B) : B(_B), cnt(0), a(), mask(), bas() {}

    std::pair<int, bool> insert(int x) {
        int tmp = x, s = 0;
        for (int i = B - 1; i >= 0; --i) {
            if (x >> i & 1) {
                if (a[i]) {
                    x ^= a[i];
                    s ^= mask[i];
                } else {
                    int v = 1 << cnt;
                    bas[cnt++] = tmp;
                    a[i] = x;
                    mask[i] = s ^ v;
                    return std::pair<int, bool>(v, true);
                }
            }
        }
        return std::pair<int, bool>(s, false);
    }

    std::vector<int> basis() const {
        return std::vector<int>(bas, bas + cnt);
    }
};

std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        v[i] = i;
    }
    for (int i = 2; i * i <= n; ++i) {
        for (int j = i * i; j <= n; j += i * i) {
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

    int lg = std::__lg(n) + 1;

    std::vector<std::pair<int, bool>> st(n + 1);
    std::vector<linear_basis> b(n + 1, linear_basis(lg));
    for (int i = 1; i <= n; ++i) {
        st[i] = b[v[i]].insert(i);
    }
    std::vector<int> mask(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (v[i] == i) {
            mask[i] = b[i].insert(f[i]).first;
        }
    }

    std::vector<int> bitcnt(1 << lg);
    for (int i = 1; i < (1 << lg); ++i) {
        bitcnt[i] = bitcnt[i >> 1] + (i & 1);
    }

    while (1) {
        std::vector<int> tmp(mask);
        std::vector<bool> sel(n + 1);
        int tot = 0;
        for (int i = 1; i <= n; ++i) {
            if (!st[i].second) {
                sel[i] = rnd() & 1;
                if (sel[i]) {
                    tmp[v[i]] ^= st[i].first;
                    ++tot;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (v[i] == i) {
                tot += bitcnt[tmp[v[i]]];
            }
        }
        if (tot == m) {
            for (int i = 1; i <= n; ++i) {
                if (sel[i]) {
                    std::cout << i << " ";
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (v[i] == i) {
                    auto bas = b[i].basis();
                    for (int j = 0; j < (int)bas.size(); ++j) {
                        if (tmp[i] >> j & 1) {
                            std::cout << bas[j] << " ";
                        }
                    }
                }
            }
            std::cout << std::endl;
            return 0;
        }
    }
}
