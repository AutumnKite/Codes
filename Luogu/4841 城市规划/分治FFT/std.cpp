#include <cstdio>
#include <algorithm>
#define N 600005
#define P 1004535809
int n, g[N], f[N], A[N], B[N], C[N], fac[N], inv[N];
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void pre(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = qpow(fac[n], P - 2);
	for (register int i = n; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
}
namespace Polynomial{
	int omega[N], rev[N];
	void init(int n){
		int k = 0;
		while ((1 << k) < n) ++k;
		for (register int i = 0; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k >> 1;
	}
	void NTT(int n, int *a, int o = 1){
		for (register int i = 0; i < n; ++i) if (i < rev[i]) std :: swap(a[i], a[rev[i]]);
		for (register int m = 1, l; m < n; m <<= 1){
			l = m << 1, omega[0] = 1, omega[1] = qpow(~o ? 3 : 334845270, (P - 1) / l);
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
	if (l == r) return f[l] = (g[l] - 1ll * fac[l - 1] * f[l] % P + P) % P, void(0);
	int mid = (l + r) >> 1;
	CDQ(l, mid);
	for (register int i = l; i <= mid; ++i) A[i - l] = 1ll * f[i] * inv[i - 1] % P;
	for (register int i = 0; i <= r - l; ++i) B[i] = 1ll * g[i] * inv[i] % P;
	Polynomial :: Multiply(mid - l + 1, A, r - l + 1, B, C);
	for (register int i = mid + 1; i <= r; ++i) (f[i] += C[i - l]) %= P;
	CDQ(mid + 1, r);
}
int main(){
	scanf("%d", &n), ++n, pre(n << 2);
	for (register int i = 1; i < n; ++i)
		g[i] = 1ll * qpow(2, (1ll * i * (i - 1) >> 1) % (P - 1)) % P;
	f[0] = 0, g[0] = 0;
	CDQ(0, n - 1);
	printf("%d\n", f[n - 1]);
}

