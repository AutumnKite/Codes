#include <bits/stdc++.h>

template<unsigned P>
class modint {
    using mint = modint<P>;

protected:
    unsigned v;

public:
    modint() : v() {}

    modint(int _v) : mint((long long)_v) {}

    modint(long long _v) {
        _v %= (long long)P;
        if (_v < 0) {
            _v += P;
        }
        v = _v;
    }

    modint(unsigned _v) : v(_v % P) {}

    modint(unsigned long long _v) : v(_v % P) {}

    operator unsigned() const {
        return v;
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
    mint operator+=(const T &rhs) {
        return *this = *this + mint(rhs);
    }

    mint operator-(const mint &rhs) const {
        return v < rhs.v ? v - rhs.v + P : v - rhs.v;
    }

    template<typename T>
    mint operator-(const T &rhs) const {
        return *this - mint(rhs);
    }

    template<typename T>
    mint operator-=(const T &rhs) {
        return *this = *this - mint(rhs);
    }

    mint operator*(const mint &rhs) const {
        return static_cast<unsigned long long>(v) * rhs.v % P;
    }

    template<typename T>
    mint operator*(const T &rhs) const {
        return *this * mint(rhs);
    }

    template<typename T>
    mint operator*=(const T &rhs) {
        return *this = *this * mint(rhs);
    }

    mint pow(unsigned long long b) const {
        mint a(*this), s(1);
        while (b) {
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
};

using mint = modint<998244353>;

const int G = 3;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

}
