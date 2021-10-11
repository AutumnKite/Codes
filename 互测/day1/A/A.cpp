#include <bits/stdc++.h>

template<unsigned P>
class modint {
    static_assert(1 <= P);

    using mint = modint<P>;

protected:
    unsigned v;

public:
    modint() : v() {}

    template<typename T, 
             typename std::enable_if<
                      std::is_signed<T>::value
                      && std::is_integral<T>::value,
                      bool>::type = true>
    modint(T _v) {
        long long tmp = _v % static_cast<long long>(P);
        if (tmp < 0) {
            tmp += P;
        }
        v = tmp;
    }

    template<typename T, 
             typename std::enable_if<
                      std::is_unsigned<T>::value
                      && std::is_integral<T>::value,
                      bool>::type = true>
    modint(T _v) {
        v = _v % P;
    }

    unsigned val() const {
        return v;
    }

    static constexpr unsigned mod() {
        return P;
    }

    static mint raw(unsigned v) {
        mint res;
        res.v = v;
        return res;
    }

    mint &operator+=(const mint &rhs) {
        v < P - rhs.v ? v += rhs.v : v -= P - rhs.v;
        return *this;
    }

    mint &operator++() {
        v + 1 < P ? ++v : v = 0;
        return *this;
    }

    mint operator++(int) {
        mint tmp = *this;
        v + 1 < P ? ++v : v = 0;
        return tmp;
    }

    mint &operator-=(const mint &rhs) {
        v < rhs.v ? v += P - rhs.v : v -= rhs.v;
        return *this;
    }

    mint &operator--() {
        v == 0 ? v = P - 1 : --v;
        return *this;
    }

    mint operator--(int) {
        mint tmp = *this;
        v == 0 ? v = P - 1 : --v;
        return tmp;
    }

    mint operator-() const {
        mint res;
        res.v = v == 0 ? 0 : P - v;
        return res;
    }

    mint &operator*=(const mint &rhs) {
        v = static_cast<unsigned long long>(v) * rhs.v % P;
        return *this;
    }

    mint pow(unsigned long long b) const {
        mint a(*this), s(1);
        for (; b; b >>= 1) {
            if (b & 1) {
                s *= a;
            }
            a *= a;
        }
        return s;
    }

    mint inv() const {
        return pow(P - 2);
    }

    friend mint operator+(const mint &lhs, const mint &rhs) {
        return mint(lhs) += rhs;
    }

    friend mint operator-(const mint &lhs, const mint &rhs) {
        return mint(lhs) -= rhs;
    }

    friend mint operator*(const mint &lhs, const mint &rhs) {
        return mint(lhs) *= rhs;
    }

    friend bool operator==(const mint &lhs, const mint &rhs) {
        return lhs.v == rhs.v;
    }

    friend bool operator!=(const mint &lhs, const mint &rhs) {
        return lhs.v != rhs.v;
    }

    friend std::istream &operator>>(std::istream &in, mint &x) {
        return in >> x.v;
    }

    friend std::ostream &operator<<(std::ostream &out, const mint &x) {
        return out << x.v;
    }
};

using mint = modint<998244353>;

class tree {
    int n;
    std::vector<mint> a, b;
    std::vector<bool> key;
    std::vector<std::vector<int>> E;
    std::vector<std::array<mint, 2>> f;

    void dfs(int u, int fa) {
        f[u][0] = 1, f[u][1] = 0;
        for (int v : E[u]) {
            if (v != fa) {
                b[v] = a[v] - a[u];
                dfs(v, u);
                f[u][1] = f[u][0] * f[v][1] + f[u][1] * f[v][0];
                f[u][0] = f[u][0] * f[v][0];
            }
        }
        if (key[u]) {
            f[u][1] = f[u][0];
            f[u][0] *= b[u];
        } else {
            f[u][0] += f[u][1] * b[u];
        }
    }

public:
    tree(const std::vector<mint> &_a, const std::vector<int> &id)
    : n(_a.size()), a(_a), b(n), key(n), E(n), f(n) {
        for (int x : id) {
            key[x] = true;
        }
    }

    void add_edge(int u, int v) {
        E[u].emplace_back(v);
        E[v].emplace_back(u);
    }

    mint get_ans(int rt) {
        b[rt] = a[rt];
        dfs(rt, -1);
        return f[rt][0];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector<mint> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    std::vector<int> nd(k);
    std::vector<bool> vis(n);
    for (int i = 0; i < k; ++i) {
        std::cin >> nd[i];
        --nd[i];
        if (vis[nd[i]]) {
            std::cout << 0 << "\n";
            return 0;
        }
        vis[nd[i]] = true;
    }

    tree T(v, nd);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        T.add_edge(u, v);
    }

    std::cout << T.get_ans(0) << "\n";
}