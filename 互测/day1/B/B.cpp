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

typedef std::bitset<5001> state;

struct node {
    state s0, s1;
    int c0, c1;

    node() : s0(), s1(), c0(), c1() {}

    node(const state &_s0, const state &_s1)
    : s0(_s0), s1(_s1), c0(s0.count()), c1(s1.count()) {}

    bool operator<(const node &rhs) const {
        return c0 > rhs.c0 || (c0 == rhs.c0 && c1 < rhs.c1);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<node> a(n);
    for (int i = 0; i < n; ++i) {
        state s1;
        std::cin >> s1;
        state s0;
        for (int j = 0; j < n; ++j) {
            s0[j] = !s1[j];
        }
        a[i] = node(s0, s1);
    }
    std::sort(a.begin(), a.end());

    std::vector<int> d(n);
    std::vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        int mx = 0;
        for (int j = 0; j < n; ++j) {
            if (a[i].s0[j]) {
                mx = std::max(mx, cnt[j]);
            } else {
                ++cnt[j];
            }
        }
        ++d[i - mx], --d[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        d[i + 1] += d[i];
    }
    state s0, s1;
    std::vector<node> b;
    for (int i = 0; i < n; ++i) {
        s0 |= a[i].s0, s1 |= a[i].s1;
        if (!d[i]) {
            b.emplace_back(s0, s1);
            s0.reset(), s1.reset();
        }
    }
    std::sort(b.begin(), b.end());

    std::vector<mint> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pw[i] = pw[i - 1] * 2;
    }

    mint ans = 0;
    int m = b.size();
    for (int i = 0; i < m - 1; ++i) {
        if ((b[i].s1 & b[i + 1].s0).none()) {
            ans += pw[n - (int)(b[i].s1 | b[i + 1].s0).count()];
        }
    }
    ans += pw[n - (int)b[0].s0.count()];
    ans += pw[n - (int)b[m - 1].s1.count()];
    for (int i = 0, j = 0; i < m; i = j) {
        j = i;
        while (j < m && b[j].s0 == b[i].s0 && b[j].s1 == b[i].s1) {
            ++j;
        }
        if ((b[i].s0 & b[i].s1).none()) {
            ans += pw[j - i] - (j - i + 1);
        }
    }
    std::cout << ans << "\n";
}
