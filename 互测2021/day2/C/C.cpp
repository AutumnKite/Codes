#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> q >> n;

    int B = sqrt(n + 1), C = n / B + 1;

    std::vector<int> l(C), r(C);
    std::vector<int> bel(n + 1);
    for (int i = 0; i <= n; ++i) {
        bel[i] = i / B;
    }
    for (int i = 0; i < C; ++i) {
        l[i] = i * B;
        r[i] = std::min((i + 1) * B - 1, n);
    }

    std::vector<int> tag(n + 1, -1);
    std::vector<int> a(n + 1, -1);
    std::vector<int> b(n + 1, -1);
    std::vector<int> c(n + 1, 0);

    auto get = [&](int x) {
        return tag[bel[x]] == -1 ? a[x] : tag[bel[x]];
    };

    auto down = [&](int x) {
        if (tag[x] != -1) {
            for (int i = l[x]; i <= r[x]; ++i) {
                a[i] = tag[x];
            }
            tag[x] = -1;
        }
    };

    auto build = [&](int x) {
        for (int i = l[x]; i <= r[x]; ++i) {
            if (a[i] < l[x]) {
                b[i] = a[i];
                c[i] = 1;
            } else {
                b[i] = b[a[i]];
                c[i] = c[a[i]] + 1;
            }
        }
    };

    while (q--) {
        int op, L, R;
        std::cin >> op >> L >> R;
        --L;
        if (op == 1) {
            int p = R - 1, q = n + 1;
            while (p + 1 < q) {
                int mid = (p + q) >> 1;
                if (get(mid) < L) {
                    p = mid;
                } else {
                    q = mid;
                }
            }
            if (R > p) {
                continue;
            }
            if (bel[R] == bel[p]) {
                down(bel[R]);
                for (int i = R; i <= p; ++i) {
                    a[i] = L;
                }
                build(bel[R]);
            } else {
                down(bel[R]);
                for (int i = R; i <= r[bel[R]]; ++i) {
                    a[i] = L;
                }
                build(bel[R]);
                for (int i = bel[R] + 1; i <= bel[p] - 1; ++i) {
                    tag[i] = L;
                }
                down(bel[p]);
                for (int i = l[bel[p]]; i <= p; ++i) {
                    a[i] = L;
                }
                build(bel[p]);
            }
        } else {
            int ans = 0;
            while (1) {
                int t = tag[bel[R]];
                if (t == -1) {
                    if (b[R] >= L) {
                        ans += c[R];
                        R = b[R];
                    } else if (a[R] >= L) {
                        ++ans;
                        R = a[R];
                    } else {
                        break;
                    }
                } else {
                    if (t >= L) {
                        ++ans;
                        R = t;
                    } else {
                        break;
                    }
                }
            }
            std::cout << ans << "\n";
        }
    }  
}