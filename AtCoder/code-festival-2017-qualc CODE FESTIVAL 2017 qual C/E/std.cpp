#include <bits/stdc++.h>

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

using mint = modint<1000000007>;

using point = std::array<long long, 3>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    point A;
    int D;
    for (int i = 0; i < 3; ++i) {
        std::cin >> A[i];
    }
    std::cin >> D;
    std::vector<point> p;
    for (int k = 0; k < 3; ++k) {
        for (int x = 0; x <= D && x < A[k]; ++x) {
            point tmp;
            tmp[k] = x;
            for (int i = 0; i < 3; ++i) {
                if (i != k) {
                    tmp[i] = x * A[i] / A[k];
                }
            }
            p.push_back(tmp);
        }
        for (int x = 0; x <= D && x < A[k]; ++x) {
            point tmp;
            tmp[k] = A[k] - 1 - x;
            for (int i = 0; i < 3; ++i) {
                if (i != k) {
                    tmp[i] = (A[k] - 1 - x) * A[i] / A[k];
                }
            }
            p.push_back(tmp);
        }
    }
    std::sort(p.begin(), p.end());
    p.erase(std::unique(p.begin(), p.end()), p.end());

    mint ans = 0;
    for (int i = 0; i + 1 < (int)p.size(); ++i) {
        point S;
        for (int k = 0; k < 3; ++k) {
            S[k] = std::min(p[i][k] + D, A[k] - 1) - std::max(p[i][k] - D, 0ll) + 1;
        }
        if (i == 0) {
            ans = 1;
            for (int k = 0; k < 3; ++k) {
                ans *= S[k];
            }
        }
        for (int k = 0; k < 3; ++k) {
            if (p[i + 1][k] + D < A[k]) {
                mint w = 1;
                for (int j = 0; j < 3; ++j) {
                    if (k != j) {
                        w *= S[j];
                    }
                }
                ans += w * (p[i + 1][k] - p[i][k]);
            }
        }
    }
    std::cout << ans << "\n";
}
