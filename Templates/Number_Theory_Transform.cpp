#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
char buf[5000000], *ps = buf, *pt, pbuf[20000000], *pp = pbuf;
inline int read(){
	register int x = 0;
	for (; !isdigit(*ps); ++ps) ;
	for (; isdigit(*ps) && ps != pt; ++ps) x = (x << 1) + (x << 3) + (*ps ^ '0');
	return x;
}
inline void print(int x){
	register int num[11], cnt;
	if (!x) *pp++ = '0';
	else{
		for (cnt = 0; x; x /= 10) num[++cnt] = x % 10 + 48;
		while (cnt) *pp++ = num[cnt], --cnt;
	}
}
#define N 2100005
#define P 998244353
struct Number_Theory_Transform{
	int n, rev[N], omega[N];
	inline void init(int m){
		n = m;
		register int k = 0;
		while ((1 << k) < n) ++k;
		for (register int i = 1; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k >> 1;
	}
	inline int qpow(int a, int b){
		register int s = 1;
		for (; b; b >>= 1, a = 1ll * a * a % P) b & 1 ? s = 1ll * s * a % P : 0;
		return s;
	}
	inline void NTT(int* a, int o){
		for (register int i = 0; i < n; ++i) i < rev[i] ? std :: swap(a[i], a[rev[i]]), 0 : 0;
		for (register int m = 1; m < n; m <<= 1){
			register int l = m << 1, omega1 = qpow(o == 1 ? 3 : 332748118, (P - 1) / l);
			omega[0] = 1;
			for (register int i = 1; i < m; ++i) omega[i] = 1ll * omega[i - 1] * omega1 % P;
			for (register int* p = a; p < a + n; p += l)
				for (register int i = 0; i < m; ++i){
					register int t = 1ll * omega[i] * p[m + i] % P;
					p[m + i] = (p[i] - t + P) % P, (p[i] += t) %= P;
				}
		}
		if (o == -1){
			register int _n = qpow(n, P - 2);
			for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * _n % P;
		}
	}
}T;
int na, nb, n, a[N], b[N];
int main(){
	pt = buf + fread(buf, 1, 5000000, stdin);
	na = read() + 1, nb = read() + 1;
	for (register int i = 0; i < na; ++i) a[i] = read();
	for (register int i = 0; i < nb; ++i) b[i] = read();
	n = 1;
	while (n < na + nb - 1) n <<= 1;
	T.init(n), T.NTT(a, 1), T.NTT(b, 1);
	for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
	T.NTT(a, -1);
	for (register int i = 0; i < na + nb - 1; ++i) print(a[i]), *pp++ = ' ';
	fwrite(pbuf, 1, pp - pbuf, stdout);
}