#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 500005
#define P 998244353
int n, g[N], f[N], A[N], B[N], C[N];
namespace Polynomial{
	int omega[N], rev[N];
	int qpow(int a, int b){
		int s = 1;
		for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
		return s;
	}
	void init(int n){
		int k = 0;
		while ((1 << k) < n) ++k;
		for (register int i = 0; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k >> 1;
	}
	void NTT(int n, int *a, int o = 1){
		for (register int i = 0; i < n; ++i) if (i < rev[i]) std :: swap(a[i], a[rev[i]]);
		for (register int m = 1, l; m < n; m <<= 1){
			l = m << 1, omega[0] = 1, omega[1] = qpow(~o ? 3 : 332748118, (P - 1) / l);
			for (register int i = 2; i < m; ++i) omega[i] = 1ll * omega[i - 1] * omega[1] % P;
			for (register int *p = a, t; p < a + n; p += l)
				for (register int k = 0; k < m; ++k)
					t = 1ll * omega[k] * p[k + m] % P, p[k + m] = (p[k] - t + P) % P, (p[k] += t) %= P;
		}
		if (o == -1) for (register int i = 0, _n = qpow(n, P - 2); i < n; ++i) a[i] = 1ll * a[i] * _n % P;
	}
	void Multiply(int na, int *a, int nb, int *b, int *c){
		int n = 1;
		while (n < na + nb - 1) n <<= 1;
		for (register int i = na; i < n; ++i) a[i] = 0;
		for (register int i = nb; i < n; ++i) b[i] = 0;
		init(n), NTT(n, a), NTT(n, b);
		for (register int i = 0; i < n; ++i) c[i] = 1ll * a[i] * b[i] % P;
		NTT(n, c, -1);
	}
}
void CDQ(int l, int r){
	if (l == r) return;
	int mid = (l + r) >> 1;
	CDQ(l, mid);
	for (register int i = l; i <= mid; ++i) A[i - l] = f[i];
	for (register int i = 0; i <= r - l; ++i) B[i] = g[i];
	Polynomial :: Multiply(mid - l + 1, A, r - l + 1, B, C);
	for (register int i = mid + 1; i <= r; ++i) (f[i] += C[i - l]) %= P;
	CDQ(mid + 1, r);
}
int main(){
	n = read();
	for (register int i = 1; i < n; ++i) g[i] = read();
	f[0] = 1, g[0] = 0;
	CDQ(0, n - 1);
	for (register int i = 0; i < n; ++i) printf("%d ", f[i]);
}

