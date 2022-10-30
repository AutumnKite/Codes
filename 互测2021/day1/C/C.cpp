#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

class seg_tree {
protected:
    struct node {
        node *ls, *rs;
        int sum;

        node() : ls(), rs(), sum() {}
    };

    int n;
    node *rt;

    void modify(node *&u, node *v, int l, int r, int x, int d) {
        if (v == nullptr) {
            u = new node();
        } else {
            u = new node(*v);
        }
        u->sum += d;
        if (l + 1 == r) {
            return;
        }
        int mid = (l + r) >> 1;
        if (x < mid) {
            modify(u->ls, v == nullptr ? nullptr : v->ls, l, mid, x, d);
        } else {
            modify(u->rs, v == nullptr ? nullptr : v->rs, mid, r, x, d);
        }
    }

    void merge(node *&u, node *v, int l, int r) {
        if (v == nullptr) {
            return;
        }
        if (u == nullptr) {
            u = new node(*v);
            return;
        }
        int mid = (l + r) >> 1;
        u = new node(*u);
        u->sum += v->sum;
        merge(u->ls, v->ls, l, mid);
        merge(u->rs, v->rs, mid, r);
    }

    int query(node *u, int l, int r, int L, int R) const {
        if (u == nullptr) {
            return 0;
        }
        if (L <= l && r <= R) {
            return u->sum;
        }
        int mid = (l + r) >> 1;
        if (R <= mid) {
            return query(u->ls, l, mid, L, R);
        } else if (L >= mid) {
            return query(u->rs, mid, r, L, R);
        } else {
            return query(u->ls, l, mid, L, R) + query(u->rs, mid, r, L, R);
        }
    }

public:
    seg_tree(int _n) : n(_n), rt() {}

    void modify(int x, int d) {
        modify(rt, rt, 0, n, x, d);
    }

    void merge(const seg_tree &rhs) {
        merge(rt, rhs.rt, 0, n);
    }

    int query(int l, int r) const {
        return query(rt, 0, n, l, r);
    }
};

struct query {
    int uA, uB, dA, dB;
    std::vector<int> col;
    std::vector<int> dep;

    query(int _uA, int _uB, int _dA, int _dB, std::vector<int> _col)
    : uA(_uA), uB(_uB), dA(_dA), dB(_dB), col(_col), dep(col.size()) {}
};

template<typename Key, typename Val>
using map = __gnu_pbds::gp_hash_table<Key, Val>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<int>> A(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        A[u].push_back(v);
        A[v].push_back(u);
    }
    std::vector<std::vector<int>> B(m);
    for (int i = 0; i < m - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        B[u].push_back(v);
        B[v].push_back(u);
    }
    std::vector<int> cA(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cA[i];
        --cA[i];
    }
    std::vector<int> cB(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> cB[i];
        --cB[i];
    }

    int idx = 0;
    std::vector<int> dfn(n), end(n), depA(n);

    auto init = [&](auto &self, int u, int fa) -> void {
        dfn[u] = idx++;
        for (int v : A[u]) {
            if (v != fa) {
                depA[v] = depA[u] + 1;
                self(self, v, u);
            }
        }
        end[u] = idx;
    };

    init(init, 0, -1);

    std::vector<query> Q;
    std::vector<std::vector<int>> id(m);
    for (int i = 0; i < q; ++i) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int p1, p2, p3, p4;
            std::cin >> p1 >> p2 >> p3 >> p4;
            --p1, --p2;
            id[p2].push_back(Q.size());
            Q.emplace_back(p1, p2, p3, p4, cA);
        } else {
            int x, c;
            std::cin >> x >> c;
            --x, --c;
            cA[x] = c;
        }
    }

    std::vector<int> depB(m);
    std::vector<map<int, int>> sub(m);
    std::vector<seg_tree> T(m, m);

    auto dfs = [&](auto &self, int u, int fa) -> void {
        sub[u][cB[u]] = depB[u];
        T[u].modify(depB[u], 1);
        for (int v : B[u]) {
            if (v != fa) {
                depB[v] = depB[u] + 1;
                self(self, v, u);
                T[u].merge(T[v]);
                if (sub[v].size() > sub[u].size()) {
                    sub[u].swap(sub[v]);
                }
                for (auto [c, d] : sub[v]) {
                    auto it = sub[u].find(c);
                    if (it == sub[u].end()) {
                        sub[u][c] = d;
                        continue;
                    }
                    if (it->second < d) {
                        T[u].modify(d, -1);
                    } else {
                        T[u].modify(it->second, -1);
                        it->second = d;
                    }
                }
            }
        }
        for (int i : id[u]) {
            for (int j = 0; j < n; ++j) {
                auto it = sub[u].find(Q[i].col[j]);
                Q[i].dep[j] = it == sub[u].end() ? -1 : it->second;
            }
        }
    };

    dfs(dfs, 0, -1);

    std::vector<int> vis(m, 0);
    int now_time = 0;
    int ans = 0;
    for (auto &[uA, uB, dA, dB, col, dep] : Q) {
        dA ^= ans;
        dB ^= ans;
        ans = T[uB].query(0, std::min(m, depB[uB] + dB + 1));
        ++now_time;
        for (int i = 0; i < n; ++i) {
            if (dfn[uA] <= dfn[i] && dfn[i] < end[uA] && depA[i] - depA[uA] <= dA) {
                if (vis[col[i]] != now_time) {
                    vis[col[i]] = now_time;
                    ++ans;
                    if (dep[i] != -1 && dep[i] - depB[uB] <= dB) {
                        --ans;
                    }
                }
            }
        }
        std::cout << ans << "\n";
    }
}
