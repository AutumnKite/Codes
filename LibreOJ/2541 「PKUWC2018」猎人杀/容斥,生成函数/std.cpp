#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
char buf[1 << 23], *ps = buf, *pt = buf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
namespace Polynomial{
#define MAX_LEN 262144
	typedef std :: vector<unsigned> poly;
	const unsigned P = 998244353, G = 3;
	poly rev;
	unsigned omega[MAX_LEN], inv[MAX_LEN];
	void inc(unsigned &a, const unsigned &b){ (a += b) >= P ? a -= P : 0; }
	void dec(unsigned &a, const unsigned &b){ a < b ? a += P - b : a -= b; }
	unsigned plus(const unsigned &a, const unsigned &b){ return a + b >= P ? a + b - P : a + b; }
	unsigned minus(const unsigned &a, const unsigned &b){ return a < b ? a + P - b : a - b; }
	unsigned mul(const unsigned &a, const unsigned &b){ return static_cast<unsigned long long>(a) * b % P; }
	unsigned qpow(unsigned a, unsigned b){
		unsigned s = 1;
		for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a);
		return s;
	}
	void Init(){
		for (register int m = 1; m < MAX_LEN; m <<= 1){
			unsigned _o = qpow(G, (P - 1) / (m << 1));
			omega[m] = 1;
			for (register int i = 1; i < m; ++i) omega[m + i] = mul(omega[m + i - 1], _o);
		}
		inv[1] = 1;
		for (register int i = 2; i < MAX_LEN; ++i) inv[i] = mul(P - P / i, inv[P % i]);
	}
	int get(int n){
		int res = 1;
		while (res < n) res <<= 1;
		return res;
	}
	void init(int n){
		int k = 0;
		while ((1 << k) < n) ++k;
		rev.resize(n), rev[0] = 0, --k;
		for (register int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
	}
	void DFT(poly &f, int n){
		f.resize(n);
		static unsigned long long ft[MAX_LEN];
		for (register int i = 0; i < n; ++i) ft[rev[i]] = f[i];
		for (register int m = 1; m < n; m <<= 1){
			register int l = m << 1;
			for (register int p = 0; p < n; p += l){
				register unsigned *W = omega + m;
				register unsigned long long *F0 = ft + p, *F1 = ft + p + m;
				for (register int i = 0; i < m; ++i, ++W, ++F0, ++F1){
					register unsigned t = (*F1) * (*W) % P;
					*F1 = (*F0) + P - t, *F0 += t;
				}
			}
		}
		for (register int i = 0; i < n; ++i) f[i] = ft[i] % P;
	}
	void IDFT(poly &f, int n){
		DFT(f, n), std :: reverse(f.begin() + 1, f.end());
		unsigned t = qpow(n, P - 2);
		for (register int i = 0; i < n; ++i) f[i] = mul(f[i], t);
	}
	poly Multiply(poly a, poly b, int _n = -1){
		if (!a.size() || !b.size() || !_n) return {};
		if (_n == -1) _n = a.size() + b.size() - 1;
		if (a.size() <= 30 || b.size() <= 30){
			poly res(a.size() + b.size() - 1);
			for (register int i = 0; i < (int)a.size(); ++i)
				for (register int j = 0; j < (int)b.size(); ++j)
					res[i + j] = (res[i + j] + 1ull * a[i] * b[j]) % P;
			for (register int i = _n; i < (int)res.size(); ++i) inc(res[i % _n], res[i]);
			return res.resize(_n), res;
		}
		int n = get(_n);
		init(n), DFT(a, n), DFT(b, n);
		for (register int i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);
		IDFT(a, n), a.resize(_n);
		return a;
	}
}
using Polynomial :: poly;
using Polynomial :: Multiply;
using Polynomial :: qpow;
const int N = 100005, P = 998244353;
int n, w[N], ans = 0;
poly solve(int l, int r){
	if (l == r){
		poly res(w[l] + 1);
		return res[w[l]] = P - 1, res[0] = 1, res;
	}
	int md = (l + r) >> 1;
	return Multiply(solve(l, md), solve(md + 1, r));
}
int main(){
	Polynomial :: Init();
	n = read();
	for (register int i = 1; i <= n; ++i) w[i] = read();
	if (n == 1) return puts("1"), 0;
	poly f = solve(2, n);
	for (register int i = 0; i < (int)f.size(); ++i)
		ans = (ans + 1ll * f[i] * qpow((i + w[1]) % P, P - 2)) % P;
	ans = 1ll * ans * w[1] % P;
	printf("%d\n", ans);
}