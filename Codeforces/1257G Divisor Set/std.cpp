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

constexpr unsigned pow_mod_constexpr(unsigned a, unsigned b, unsigned P) {
    unsigned s = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            s = static_cast<unsigned long long>(s) * a % P;
        }
        a = static_cast<unsigned long long>(a) * a % P;
    }
    return s;
}

constexpr unsigned primitive_root(unsigned n) {
    if (n == 998244353) {
        return 3;
    }
    unsigned x = n - 1;
    int cnt = 0;
    int div[20] = {};
    for (unsigned i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            div[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        div[cnt++] = x;
    }
    int g = 1;
    while (1) {
        bool ok = true;
        for (int i = 0; i < cnt; ++i) {
            if (pow_mod_constexpr(g, (n - 1) / div[i], n) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return g;
        }
        ++g;
    }
    return 0;
}

template<unsigned P, unsigned L>
class modpoly {
    using mint = modint<P>;
    using poly = modpoly<P, L>;

public:
    typedef std::size_t size_type;

    static constexpr unsigned root = primitive_root(P);

protected:
    struct initializer {
        static constexpr size_type N = static_cast<size_type>(1) << L;

        mint omega[N], inv[N + 1];

        initializer() {
            for (size_type m = 1; m < N; m <<= 1) {
                mint w = mint(root).pow((P - 1) / (m << 1));
                omega[m] = 1;
                for (size_type i = 1; i < m; ++i) {
                    omega[m + i] = omega[m + i - 1] * w;
                }
            }

            inv[1] = 1;
            for (size_type i = 2; i <= N; ++i) {
                inv[i] = -mint(static_cast<unsigned>(P / i)) * inv[P % i];
            }
        }

        std::vector<size_type> rev;

        void build_rev(size_type n) {
            if (n == rev.size()) {
                return;
            }
            size_type k = 0;
            while ((static_cast<size_type>(1) << k) < n) {
                ++k;
            }
            rev.resize(n);
            rev[0] = 0;
            for (size_type i = 1; i < n; ++i) {
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
            }
        }
    };
    
    static initializer init;

    static constexpr unsigned DFT_mod_cnt = 
      std::min(std::numeric_limits<unsigned long long>::max()
          / (static_cast<unsigned long long>(P) * P) - 1, 
        static_cast<unsigned long long>(L));

    std::vector<mint> f;

    static constexpr size_type enlarge_to_pow2(size_type n) {
        size_type res = 1;
        while (res < n) {
            res <<= 1;
        }
        return res;
    }

public:
    modpoly() {}

    modpoly(size_type n) : f(n) {}

    modpoly(const std::vector<mint> &_f) : f(_f) {}

    modpoly(mint v) : f(1, v) {}

    const std::vector<mint> &vec() const {
        return f;
    }

    std::vector<mint> &vec() {
        return f;
    }

    bool empty() const {
        return f.empty();
    }

    size_type size() const {
        return f.size();
    }

    typename std::vector<mint>::reference operator[](size_type x) {
        return f[x];
    }

    typename std::vector<mint>::const_reference operator[](size_type x) const {
        return f[x];
    }

    void DFT(size_type n) {
        init.build_rev(n);
        f.resize(n);
        static unsigned long long F[initializer::N];
        for (size_type i = 0; i < n; ++i) {
            F[init.rev[i]] = f[i].val();
        }
        for (size_type m = 1; m < n; m <<= 1) {
            if (m & (static_cast<size_type>(1) << DFT_mod_cnt)) {
                for (size_type i = 0; i < n; ++i) {
                    F[i] %= P;
                }
            }
            for (size_type p = 0; p < n; p += m << 1) {
                mint *W = init.omega + m;
                unsigned long long *F0 = F + p, *F1 = F + p + m;
                for (size_type i = 0; i < m; ++i, ++W, ++F0, ++F1) {
                    unsigned t = (*F1) * W->val() % P;
                    *F1 = *F0 + P - t, *F0 += t;
                }
            }
        }
        for (size_type i = 0; i < n; ++i) {
            f[i] = F[i];
        }
    }

    void IDFT(size_type n) {
        DFT(n);
        std::reverse(f.begin() + 1, f.end());
        mint t = init.inv[n];
        for (size_type i = 0; i < n; ++i) {
            f[i] *= t;
        }
    }

    void mul_in(poly &b, size_type _n = static_cast<size_type>(-1)) {
        poly &a = *this;
        if (a.empty() || b.empty() || !_n) {
            f.clear();
            return;
        }
        _n = std::min(_n, a.size() + b.size() - 1);
        if (a.size() <= 30 || b.size() <= 30) {
            std::vector<mint> res(a.size() + b.size() - 1);
            for (size_type i = 0; i < a.size(); ++i) {
                for (size_type j = 0; j < b.size(); ++j) {
                    res[i + j] += a.f[i] * b.f[j];
                }
            }
            res.resize(_n);
            f.swap(res);
            return;
        }
        size_type n = enlarge_to_pow2(_n);
        a.DFT(n), b.DFT(n);
        for (size_type i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        a.IDFT(n);
        a.vec().resize(_n);
    }

    friend poly mul(poly a, poly b, size_type _n = static_cast<size_type>(-1)) {
        a.mul_in(b, _n);
        return a;
    }

    poly &operator+=(const poly &rhs) {
        if (rhs.size() > f.size()) {
            f.resize(rhs.size());
        }
        for (size_type i = 0; i < rhs.size(); ++i) {
            f[i] += rhs[i];
        }
        return *this;
    }

    poly &operator-=(const poly &rhs) {
        if (rhs.size() > f.size()) {
            f.resize(rhs.size());
        }
        for (size_type i = 0; i < rhs.size(); ++i) {
            f[i] -= rhs[i];
        }
        return *this;
    }

    poly &operator*=(const poly &rhs) {
        poly tmp(rhs);
        mul_in(tmp);
        return *this;
    }

    poly &operator*=(const mint &rhs) {
        for (size_type i = 0; i < f.size(); ++i) {
            f[i] *= rhs;
        }
        return *this;
    }

    friend poly operator+(const poly &lhs, const poly &rhs) {
        return poly(lhs) += rhs;
    }

    friend poly operator-(const poly &lhs, const poly &rhs) {
        return poly(lhs) -= rhs;
    }

    friend poly operator*(const poly &lhs, const poly &rhs) {
        return mul(lhs, rhs);
    }

    friend poly operator*(const poly &lhs, const mint &rhs) {
        return poly(lhs) *= rhs;
    }
};

template<unsigned P, unsigned L>
typename modpoly<P, L>::initializer modpoly<P, L>::init;

using mint = modint<998244353>;
using poly = modpoly<998244353, 18>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        ++cnt[v];
    }
    std::vector<int> d;
    for (auto [p, c] : cnt) {
        d.push_back(c);
    }

    auto solve = [&](auto self, int l, int r) {
        if (l + 1 == r) {
            return poly(std::vector<mint>(d[l] + 1, 1));
        }
        int mid = (l + r + 1) >> 1;
        return self(self, l, mid) * self(self, mid, r);
    };

    std::cout << solve(solve, 0, d.size())[n / 2] << "\n";
}
