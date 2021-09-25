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

const int N = 2000000;

mint fac[N + 1], ifac[N + 1];

void init() {
    fac[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fac[i] = fac[i - 1] * i;
    }
    ifac[N] = fac[N].inv();
    for (int i = N; i >= 1; --i) {
        ifac[i - 1] = ifac[i] * i;
    }
}

mint P(int n, int m) {
    return fac[n + m] * ifac[n] * ifac[m];
}

mint solve(int X1, int Y1, int X2, int Y2,
           int Sx, int Sy, int Tx, int Ty) {
    mint ans = 0;
    for (int i = Sx; i <= Tx; ++i) {
        mint Sv = mint::raw(i + Sy), Tv = mint::raw(i + 1 + Ty);
        ans -= P(i - X1 + 1, Sy - Y1) * P(X2 - i + 1, Y2 - Sy + 1) * Sv;
        ans += P(X2 - i + 1, Y2 - Ty) * P(i - X1 + 1, Ty - Y1 + 1) * Tv;
    }
    for (int i = Sy; i <= Ty; ++i) {
        mint Sv = mint::raw(i + Sx), Tv = mint::raw(i + 1 + Tx);
        ans -= P(i - Y1 + 1, Sx - X1) * P(Y2 - i + 1, X2 - Sx + 1) * Sv;
        ans += P(Y2 - i + 1, X2 - Tx) * P(i - Y1 + 1, Tx - X1 + 1) * Tv;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    init();

    int sx1, tx1, sx2, tx2, sx3, tx3;
    std::cin >> sx1 >> tx1 >> sx2 >> tx2 >> sx3 >> tx3;
    int sy1, ty1, sy2, ty2, sy3, ty3;
    std::cin >> sy1 >> ty1 >> sy2 >> ty2 >> sy3 >> ty3;

    ++tx1, ++ty1;
    --sx3, --sy3;

    mint ans = 0;
    ans += solve(sx1, sy1, tx3, ty3, sx2, sy2, tx2, ty2);
    ans -= solve(sx1, sy1, tx3, sy3, sx2, sy2, tx2, ty2);
    ans -= solve(sx1, sy1, sx3, ty3, sx2, sy2, tx2, ty2);
    ans += solve(sx1, sy1, sx3, sy3, sx2, sy2, tx2, ty2);
    ans -= solve(sx1, ty1, tx3, ty3, sx2, sy2, tx2, ty2);
    ans += solve(sx1, ty1, tx3, sy3, sx2, sy2, tx2, ty2);
    ans += solve(sx1, ty1, sx3, ty3, sx2, sy2, tx2, ty2);
    ans -= solve(sx1, ty1, sx3, sy3, sx2, sy2, tx2, ty2);
    ans -= solve(tx1, sy1, tx3, ty3, sx2, sy2, tx2, ty2);
    ans += solve(tx1, sy1, tx3, sy3, sx2, sy2, tx2, ty2);
    ans += solve(tx1, sy1, sx3, ty3, sx2, sy2, tx2, ty2);
    ans -= solve(tx1, sy1, sx3, sy3, sx2, sy2, tx2, ty2);
    ans += solve(tx1, ty1, tx3, ty3, sx2, sy2, tx2, ty2);
    ans -= solve(tx1, ty1, tx3, sy3, sx2, sy2, tx2, ty2);
    ans -= solve(tx1, ty1, sx3, ty3, sx2, sy2, tx2, ty2);
    ans += solve(tx1, ty1, sx3, sy3, sx2, sy2, tx2, ty2);
    std::cout << ans << "\n";
}
