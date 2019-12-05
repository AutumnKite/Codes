#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
// char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
// #define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
// #define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
// struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int P = 998244353, G = 3;
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
void dec(int &a, int b){ (a -= b) < 0 ? a += P : 0; }
int plus(int a, int b){ return (a += b) >= P ? a - P : a; }
int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
namespace Polynomial{
	typedef std :: vector<int> poly;
	poly rev, omega;
	int get(int _n){
		int n = 1;
		while (n < _n) n <<= 1;
		return n;
	}
	void init(int n){
		int k = 0;
		while ((1 << k) < n) ++k;
		rev.resize(n), omega.resize(n);
		rev[0] = 0, --k;
		for (register int i = 1; i < n; ++i)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
		for (register int m = 1; m < n; m <<= 1){
			int _o = qpow(G, (P - 1) / (m << 1));
			omega[m] = 1;
			for (register int i = 1; i < m; ++i) omega[m + i] = 1ll * omega[m + i - 1] * _o % P;
		}
	}
	void DFT(poly &f, int n){
		f.resize(n);
		for (register int i = 0; i < n; ++i) if (i < rev[i]) std :: swap(f[i], f[rev[i]]);
		for (register int m = 1; m < n; m <<= 1){
			int l = m << 1;
			for (poly :: iterator W = omega.begin() + m, F = f.begin(); F != f.end(); F += l)
				for (register int i = 0; i < m; ++i){
					register int t = 1ll * F[i + m] * W[i] % P;
					F[i + m] = minus(F[i], t), inc(F[i], t);
				}
		}
	}
	void IDFT(poly &f, int n){
		DFT(f, n), std :: reverse(f.begin() + 1, f.end());
		for (register int _n = qpow(n, P - 2), i = 0; i < n; ++i) f[i] = 1ll * f[i] * _n % P;
	}
	poly Multiply(poly a, poly b){
		if (!a.size() || !b.size()) return {};
		if (a.size() <= 30 || b.size() <= 30){
			poly res(a.size() + b.size() - 1);
			for (register int i = 0; i < a.size(); ++i)
				for (register int j = 0; j < b.size(); ++j)
					res[i + j] = (res[i + j] + 1ll * a[i] * b[j]) % P;
			return res;
		}
		int _n = a.size() + b.size() - 1, n = get(_n);
		init(n), DFT(a, n), DFT(b, n);
		for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
		IDFT(a, n), a.resize(_n);
		return a;
	}
	poly Inverse(poly f, int _n){
		int n = get(_n);
		f.resize(n);
		poly g(1);
		g[0] = qpow(f[0], P - 2);
		for (register int m = 2; m <= n; m <<= 1){
			poly tmp(m);
			for (register int i = 0; i < m; ++i) tmp[i] = f[i];
			int l = m << 1;
			init(l), DFT(tmp, l), DFT(g, l);
			for (register int i = 0; i < l; ++i)
				g[i] = 1ll * g[i] * minus(2, 1ll * tmp[i] * g[i] % P) % P;
			IDFT(g, l), g.resize(m);
		}
		return g.resize(_n), g;
	}
	poly Derivative(poly f){
		int n = f.size();
		for (register int i = 1; i < n; ++i) f[i - 1] = 1ll * f[i] * i % P;
		return f.resize(n - 1), f;
	}
	poly Integral(poly f){
		f.push_back(0);
		int n = f.size();
		poly inv(n);
		inv[1] = 1;
		for (register int i = 2; i < n; ++i) inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
		for (register int i = n - 1; i; --i) f[i] = 1ll * f[i - 1] * inv[i] % P;
		return f[0] = 0, f;
	}
	poly Ln(const poly &f, int n){
		poly res = Integral(Multiply(Derivative(f), Inverse(f, n)));
		return res.resize(n), res;
	}
}
using Polynomial :: poly;
using Polynomial :: Ln;
using Polynomial :: Multiply;
using Polynomial :: Derivative;
const int N = 100005;
int n, m, a[N], b[N], t, fac[N], inv[N];
poly solve(int *a, int l, int r){
	if (l + 1 == r) return {1, minus(0, a[l])};
	int md = (l + r + 1) >> 1;
	return Multiply(solve(a, l, md), solve(a, md, r));
}
void get_g(int *a, int n, poly &g){
	g = solve(a, 0, n);
	g = Derivative(Ln(g, t));
	g.push_back(0);
	for (register int i = t - 1; i; --i) g[i] = minus(0, g[i - 1]);
	g[0] = n;
}
void init(int n){
	fac[0] = 1;
	for (register int i = 1; i < n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n - 1] = qpow(fac[n - 1], P - 2);
	for (register int i = n - 1; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
}
int main(){
	n = read(), m = read();
	for (register int i = 0; i < n; ++i) a[i] = read();
	for (register int i = 0; i < m; ++i) b[i] = read();
	t = read() + 1;
	poly ga, gb;
	get_g(a, n, ga), get_g(b, m, gb);
	init(t);
	for (register int i = 0; i < t; ++i) ga[i] = 1ll * ga[i] * inv[i] % P;
	for (register int i = 0; i < t; ++i) gb[i] = 1ll * gb[i] * inv[i] % P;
	poly res = Multiply(ga, gb);
	for (register int i = 1; i < t; ++i) print(1ll * res[i] * fac[i] % P);
}