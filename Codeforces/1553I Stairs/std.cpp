#include <bits/stdc++.h>

std::pair<int, int> a;

template<unsigned P>
class modint {
    static_assert(1 <= P);

    using mint = modint<P>;

protected:
    unsigned v;

public:
    modint() : v() {}

    template<typename T, typename std::enable_if<
      std::is_signed<T>::value && std::is_integral<T>
        ::value, bool>::type = true>
    modint(T _v) {
        long long tmp = _v % static_cast<long long>(P);
        if (tmp < 0) {
            tmp += P;
        }
        v = tmp;
    }

    template<typename T, typename std::enable_if<
      std::is_unsigned<T>::value && std::is_integral<T>
        ::value, bool>::type = true>
    modint(T _v) {
        v = _v % P;
    }

    operator unsigned() const {
        return v;
    }

    constexpr unsigned mod() {
        return P;
    }

    mint operator-() const {
        mint res;
        if (v) {
            res.v = P - v;
        }
        return res;
    }

    mint operator+(const mint &rhs) const {
        return v < P - rhs.v ? v + rhs.v : v + rhs.v - P;
    }

    template<typename T>
    mint operator+(const T &rhs) const {
        return *this + mint(rhs);
    }

    template<typename T>
    mint &operator+=(const T &rhs) {
        return *this = *this + mint(rhs);
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

    mint operator-(const mint &rhs) const {
        return v < rhs.v ? v - rhs.v + P : v - rhs.v;
    }

    template<typename T>
    mint operator-(const T &rhs) const {
        return *this - mint(rhs);
    }

    template<typename T>
    mint &operator-=(const T &rhs) {
        return *this = *this - mint(rhs);
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

    mint operator*(const mint &rhs) const {
        return static_cast<unsigned long long>(v) * rhs.v % P;
    }

    template<typename T>
    mint operator*(const T &rhs) const {
        return *this * mint(rhs);
    }

    template<typename T>
    mint &operator*=(const T &rhs) {
        return *this = *this * mint(rhs);
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

    friend std::istream &operator>>(std::istream &in, mint &x) {
        return in >> x.v;
    }
};

constexpr unsigned __pow_mod_constexpr(unsigned a, unsigned b, unsigned P) {
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
            if (__pow_mod_constexpr(g, (n - 1) / div[i], n) == 1) {
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
class polyP {
    using mint = modint<P>;
    using poly = polyP<P, L>;

public:
    typedef std::size_t size_type;

    static constexpr unsigned root = primitive_root(P);

protected:
    struct __init {
        static constexpr size_type N = static_cast<size_type>(1) << L;

        mint omega[N], inv[N + 1];

        __init() {
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
    
    static __init init;

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
    polyP() {}

    polyP(size_type n) : f(n) {}

    polyP(const std::vector<mint> &_f) : f(_f) {}

    polyP(mint v) : f(1, v) {}

    const std::vector<mint> &vec() const {
        return f;
    }

    std::vector<mint> &vec() {
        return f;
    }

    bool empty() {
        return f.empty();
    }

    size_type size() {
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
        static unsigned long long F[__init::N];
        for (size_type i = 0; i < n; ++i) {
            F[init.rev[i]] = f[i];
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
                    unsigned t = (*F1) * (*W) % P;
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

    friend poly mul(poly a, poly b, size_type _n = static_cast<size_type>(-1)) {
        if (a.empty() || b.empty() || !_n) {
            return poly();
        }
        _n = std::min(_n, a.size() + b.size() - 1);
        size_type n = enlarge_to_pow2(_n);
        a.DFT(n), b.DFT(n);
        for (size_type i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        a.IDFT(n);
        a.vec().resize(_n);
        return a;
    }
};

template<unsigned P, unsigned L> typename polyP<P, L>::__init polyP<P, L>::init;

using poly = polyP<998244353, 21>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

}
