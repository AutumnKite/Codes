#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
struct BigInt{
	static const int Num = 9, P = 1000000000, N = 2005;
	int len;
	long long a[N];
	bool operator > (const BigInt &x) const {
		if (len != x.len) return len > x.len;
		for (register int i = len; i; --i)
			if (a[i] != x.a[i]) return a[i] > x.a[i];
		return false;
	}
	bool operator != (const BigInt &x) const {
		if (len != x.len) return true;
		for (register int i = len; i; --i)
			if (a[i] != x.a[i]) return true;
		return false;
	}
	BigInt operator = (int x) {
		for (len = 0; x; x /= P) a[++len] = x % P;
		return *this;
	}
	BigInt operator = (char* x) {
		int L = strlen(x + 1), pre = L % Num;
		len = L / Num + (pre > 0);
		for (register int i = len, j = 1, k = 0; j <= L; ++j){
			k = k * 10 + x[j] - 48;
			if (j % Num == pre) a[i] = k, k = 0, --i;
		}
		return *this;
	}
	BigInt operator - (const BigInt &x) const {
		BigInt y (*this), ret;
		ret.len = y.len, memset(ret.a, 0, sizeof ret.a);
		for (register int i = 1; i <= ret.len; ++i){
			if (y.a[i] < x.a[i]) --y.a[i + 1], y.a[i] += P;
			ret.a[i] = y.a[i] - x.a[i];
		}
		while (!ret.a[ret.len] && ret.len > 1) --ret.len;
		return ret;
	}
	BigInt &operator -= (const BigInt &x) {
		return *this = *this - x;
	}
	BigInt operator * (const BigInt &x) const {
		BigInt ret;
		ret.len = x.len + this->len - 1, memset(ret.a, 0, sizeof ret.a);
		for (register int i = 1; i <= x.len; ++i)
			for (register int j = 1; j <= this->len; ++j)
				ret.a[i + j - 1] += x.a[i] * this->a[j],
				ret.a[i + j] += ret.a[i + j - 1] / P,
				ret.a[i + j - 1] %= P;
		if (ret.a[ret.len + 1]) ++ret.len;
		while (!ret.a[ret.len] && ret.len > 1) --ret.len;
		return ret;
	}
	BigInt &operator *= (const BigInt &x) {
		return *this = *this * x;
	}
	void divi () {
		for (register int i = len; i; --i)
			a[i - 1] += (a[i] & 1) * P, a[i] >>= 1;
		while (!a[len] && len > 1) --len;
		a[0] = 0;
	}
	friend std :: ostream &operator << (std :: ostream &out, const BigInt &x) {
	    printf("%lld", x.a[x.len]);
	    for (register int i = x.len - 1; i; --i)
	        printf("%0*lld", x.Num, x.a[i]);
	    return out;
	}
	friend std :: istream &operator >> (std :: istream &in, BigInt &x) {
	    char str[x.N * x.Num + 5];
	    scanf("%s", str + 1);
	    x = str;
	    return in;
	}
}a, b, c, g;
int main(){
	std :: cin >> a >> b;
	c = 2, g = 1;
	while (a != b){
		int A = a.a[1] & 1, B = b.a[1] & 1;
		if (A && B) if (a > b) a -= b; else b -= a;
		if (A && !B) b.divi();
		if (!A && B) a.divi();
		if (!A && !B) a.divi(), b.divi(), g *= c;
	} 
	std :: cout << g * a;
}
