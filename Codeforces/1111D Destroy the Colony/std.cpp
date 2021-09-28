#include <bits/stdc++.h>

template<unsigned P>
class modint {
    static_assert(1 <= P);

    using mint = modint<P>;

protected:
    unsigned v;

public:
    modint() : v() {}

    template<typename T, typename std::enable_if<std::__and_<
      std::is_signed<T>, std::is_integral<T>>::value, bool>::type = true>
    modint(T _v) {
        long long tmp = _v % static_cast<long long>(P);
        if (tmp < 0) {
            tmp += P;
        }
        v = tmp;
    }

    template<typename T, typename std::enable_if<std::__and_<
      std::is_unsigned<T>, std::is_integral<T>>::value, bool>::type = true>
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
        return mint(0) -= *this;
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

using mint = modint<1000000007>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;
    int n = s.size(), m = n / 2;
    
    auto get_id = [&](char c) {
        if (isupper(c)) {
            return c - 'A';
        } else {
            return c - 'a' + 26;
        }
    };

    std::vector<int> cnt(52);
    for (int i = 0; i < n; ++i) {
        ++cnt[get_id(s[i])];
    }

    std::vector<mint> fac(n + 1), ifac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = fac[i - 1] * i;
    }
    ifac[n] = fac[n].inv();
    for (int i = n; i >= 1; --i) {
        ifac[i - 1] = ifac[i] * i;
    }

    mint prod = 1;
    for (int i = 0; i < 52; ++i) {
        prod *= ifac[cnt[i]];
    }

    std::vector<mint> f(m + 1);
    f[0] = 1;
    for (int i = 0; i < 52; ++i) {
        if (cnt[i]) {
            for (int k = m; k >= cnt[i]; --k) {
                f[k] += f[k - cnt[i]];
            }
        }
    }

    std::vector<std::vector<mint>> ans(52, std::vector<mint>(52));
    for (int i = 0; i < 52; ++i) {
        if (cnt[i]) {
            auto g(f);
            for (int k = cnt[i]; k <= m; ++k) {
                g[k] -= g[k - cnt[i]];
            }
            for (int j = i + 1; j < 52; ++j) {
                if (cnt[j]) {
                    mint s = 0;
                    for (int k = m, p = 0; k >= 0; k -= cnt[j]) {
                        if (p) {
                            s -= g[k];
                        } else {
                            s += g[k];
                        }
                        p = !p;
                    }
                    for (int k = m - cnt[i] - cnt[j], p = 0; k >= 0; k -= cnt[j]) {
                        if (p) {
                            s -= g[k];
                        } else {
                            s += g[k];
                        }
                        p = !p;
                    }
                    ans[i][j] = ans[j][i] = s;
                }
            }
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        int a = get_id(s[x]), b = get_id(s[y]);
        if (a == b) {
            std::cout << f[m] * fac[m] * fac[m] * prod << "\n";
        } else {
            std::cout << ans[a][b] * fac[m] * fac[m] * prod << "\n";
        }
    }
}
