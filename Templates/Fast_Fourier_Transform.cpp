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
struct complex{
	double re, im;
	inline complex operator + (const complex &a) const {
		return (complex){re + a.re, im + a.im};
	}
	inline complex operator - (const complex &a) const {
		return (complex){re - a.re, im - a.im};
	}
	inline complex operator * (const complex &a) const {
		return (complex){re * a.re - im * a.im, re * a.im + im * a.re};
	}
};
struct Fast_Fourier_Transform{
	int n, rev[N];
	complex omega[N];
	inline void init(int m){
		n = m;
		register int k = 0;
		while ((1 << k) < n) ++k;
		for (register int i = 1; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k >> 1;
	}
	inline void FFT(complex* a, int o){
		for (register int i = 0; i < n; ++i) i < rev[i] ? std :: swap(a[i], a[rev[i]]), 0 : 0;
		for (register int m = 1; m < n; m <<= 1){
			register int l = m << 1;
			register complex omega1 = (complex){cos(3.14159265 / m), o * sin(3.14159265 / m)};
			omega[0] = (complex){1, 0};
			for (register int i = 1; i < m; ++i) omega[i] = omega[i - 1] * omega1;
			for (register complex* p = a; p < a + n; p += l)
				for (register int i = 0; i < m; ++i){
					register complex t = omega[i] * p[m + i];
					p[m + i] = p[i] - t, p[i] = p[i] + t;
				}
		}
		if (o == -1) for (register int i = 0; i < n; ++i) a[i].re /= n;
	}
}T;
int na, nb, n;
complex a[N], b[N];
int main(){
	pt = buf + fread(buf, 1, 5000000, stdin);
	na = read() + 1, nb = read() + 1;
	for (register int i = 0; i < na; ++i) a[i] = (complex){(double)read(), 0};
	for (register int i = 0; i < nb; ++i) b[i] = (complex){(double)read(), 0};
	n = 1;
	while (n < na + nb - 1) n <<= 1;
	T.init(n), T.FFT(a, 1), T.FFT(b, 1);
	for (register int i = 0; i < n; ++i) a[i] = a[i] * b[i];
	T.FFT(a, -1);
	for (register int i = 0; i < na + nb - 1; ++i) print(floor(a[i].re + 0.5)), *pp++ = ' ';
	fwrite(pbuf, 1, pp - pbuf, stdout);
}