#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 300005
#define INF 0x3f3f3f3f3f3f3f3fll
int n, m, a[N], b[N], c[N];
namespace Polynomial{
	#define P 998244353
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
	void add(int &x, int y){ (x += y) >= P ? x -= P : 0; }
	int sub(int x, int y){ return (x -= y) < 0 ? x + P : x; }
	void NTT(int n, int *a, int o = 1){
		for (register int i = 0; i < n; ++i) if (i < rev[i]) std :: swap(a[i], a[rev[i]]);
		for (register int m = 1, l; m < n; m = l){
			l = m << 1, omega[0] = 1, omega[1] = qpow(~o ? 3 : 332748118, (P - 1) / l);
			for (register int i = 2; i < m; ++i) omega[i] = 1ll * omega[i - 1] * omega[1] % P;
			for (register int *p = a, t; p < a + n; p += l)
				for (register int k = 0; k < m; ++k)
					t = 1ll * p[k + m] * omega[k] % P, p[k + m] = sub(p[k], t), add(p[k], t);
		}
		if (o == -1)
			for (register int _n = qpow(n, P - 2), i = 0; i < n; ++i) a[i] = 1ll * a[i] * _n % P;
	}
	void Multiply(int na, int *a, int nb, int *b, int nc, int *c){
		int n = 1;
		while (n < nc) n <<= 1;
		init(n), NTT(n, a), NTT(n, b);
		for (register int i = 0; i < n; ++i) c[i] = 1ll * a[i] * b[i] % P;
		NTT(n, c, -1);
	}
}
int main(){
	long long s1 = 0, s2 = 0, s = INF, ans = INF;
	n = read(), m = read();
	for (register int i = 0; i < n; ++i) a[n - i - 1] = read();
	for (register int i = 0; i < n; ++i) b[i + n] = b[i] = read();
	for (register int i = 0; i < n; ++i)
		s1 += 1ll * a[i] * a[i] + 1ll * b[i] * b[i], s2 += (a[i] << 1) - (b[i] << 1);
	Polynomial :: Multiply(n, a, n << 1, b, n << 1, c);
	// for (register int i = n - 1; i < (n << 1) - 1; ++i) printf("%d ", c[i]); putchar('\n');
	for (register int i = n - 1; i < (n << 1) - 1; ++i) s = std :: min(s, -2ll * c[i]);
	for (register int i = -m; i <= m; ++i)
		ans = std :: min(ans, 1ll * n * i * i + s2 * i + s1);
	printf("%lld\n", ans + s);
	getchar(), getchar();
}