#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 300005
#define P1 998244353
#define P2 1004535809
#define P3 469762049
#define G 3
#define I1 332748118
#define I2 334845270
#define I3 156587350
int mod;
int add(int x, int y, int P){
	return (x += y) >= P ? x - P : x;
}
int del(int x, int y, int P){
	return (x -= y) < 0 ? x + P : x;
}
int mul(int x, int y, int P){
	return 1ll * x * y % P;
}
int qpow(int a, int b, int P){
    register int s = 1;
    for (; b; b >>= 1, a = 1ll * a * a % P) b & 1 ? s = 1ll * s * a % P : 0;
    return s;
}
const long long M = 1ll * P1 * P2;
int Inv1, Inv2;
struct Int{
	int A, B, C;
	Int(){ A = B = C = 0; }
	Int(int x){ A = x % P1, B = x % P2, C = x % P3; }
	Int(int _A, int _B, int _C){ A = _A, B = _B, C = _C; }
	void operator = (const int x){
		A = x % P1, B = x % P2, C = x % P3;
	}
	Int operator + (const Int &rhs) const {
		return Int(add(A, rhs.A, P1), add(B, rhs.B, P2), add(C, rhs.C, P3));
	}
	Int operator - (const Int &rhs) const {
		return Int(del(A, rhs.A, P1), del(B, rhs.B, P2), del(C, rhs.C, P3));
	}
	Int operator * (const Int &rhs) const {
		return Int(mul(A, rhs.A, P1), mul(B, rhs.B, P2), mul(C, rhs.C, P3));
	}
	int get(){
		long long x = 1ll * del(B, A, P2) * Inv1 % P2 * P1 + A;
		return (1ll * del(C, x % P3, P3) * Inv2 % P3 * (M % mod) % mod + x) % mod;
	}
};
Int qpow(Int a, int b){
	Int s = 1;
	for (; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
	return s;
}
struct Number_Theory_Transform{
	int n, rev[N];
	Int omega[N];
	void init(int m){
		n = m;
		register int k = 0;
		while ((1 << k) < n) ++k;
		for (register int i = 1; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k >> 1;
	}
	void NTT(Int* a, int o){
		for (register int i = 0; i < n; ++i) i < rev[i] ? std :: swap(a[i], a[rev[i]]), 0 : 0;
		for (register int m = 1; m < n; m <<= 1){
			register int l = m << 1;
			Int omega1(qpow(o == 1 ? G : I1, (P1 - 1) / l, P1), 
						qpow(o == 1 ? G : I2, (P2 - 1) / l, P2), 
						qpow(o == 1 ? G : I3, (P3 - 1) / l, P3));
			omega[0] = 1;
			for (register int i = 1; i < m; ++i) omega[i] = omega[i - 1] * omega1;
			for (register Int* p = a; p < a + n; p += l)
				for (register int i = 0; i < m; ++i){
					register Int t = omega[i] * p[m + i];
					p[m + i] = p[i] - t, p[i] = p[i] + t;
				}
		}
		if (o == -1){
			register Int _n(qpow(n, P1 - 2, P1), qpow(n, P2 - 2, P2), qpow(n, P3 - 2, P3));
			for (register int i = 0; i < n; ++i) a[i] = a[i] * _n;
		}
	}
}T;
int na, nb, n;
Int a[N], b[N];
int main(){
	Inv1 = qpow(P1, P2 - 2, P2), Inv2 = qpow(M % P3, P3 - 2, P3);
    na = read() + 1, nb = read() + 1, mod = read();
    for (register int i = 0; i < na; ++i) a[i] = read();
    for (register int i = 0; i < nb; ++i) b[i] = read();
    n = 1;
    while (n < na + nb - 1) n <<= 1;
    T.init(n), T.NTT(a, 1), T.NTT(b, 1);
    for (register int i = 0; i < n; ++i) a[i] = a[i] * b[i];
    T.NTT(a, -1);
    for (register int i = 0; i < na + nb - 1; ++i) printf("%d ", a[i].get());
}

