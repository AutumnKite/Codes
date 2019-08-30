#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define N 500005
int n;
double a[N];
namespace Polynomial{
	const long double PI = acos(-1);
	struct complex{
		long double re, im;
		complex operator + (const complex &res) const {
			return (complex){re + res.re, im + res.im};
		}
		complex operator - (const complex &res) const {
			return (complex){re - res.re, im - res.im};
		}
		complex operator * (const complex &res) const {
			return (complex){re * res.re - im * res.im, re * res.im + im * res.re};
		}
	};
	complex omega[N];
	int rev[N];
	void init(int n){
		int k = 0;
		while ((1 << k) < n) ++k;
		for (register int i = 0; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k >> 1;
	}
	void FFT(int n, complex *a, int o = 1){
		for (register int i = 0; i < n; ++i) if (i < rev[i]) std :: swap(a[i], a[rev[i]]);
		for (register int m = 1, l; m < n; m <<= 1){
			l = m << 1;
			omega[0] = (complex){1, 0};
			omega[1] = (complex){cos(PI / m), o * sin(PI / m)};
			for (register int i = 2; i < m; ++i) omega[i] = omega[i - 1] * omega[1];
			for (register complex *p = a, t; p < a + n; p += l)
				for (register int k = 0; k < m; ++k)
					t = omega[k] * p[k + m], p[k + m] = p[k] - t, p[k] = p[k] + t;
		}
		if (o == -1) for (register int i = 0; i < n; ++i) a[i].re /= n;
	}
	void Multiply(int na, complex *a, int nb, complex *b, complex *c){
		int n = 1;
		while (n < na + nb - 1) n <<= 1;
		init(n), FFT(n, a), FFT(n, b);
		for (register int i = 0; i < n; ++i) c[i] = a[i] * b[i];
		FFT(n, c, -1);
	}
}
Polynomial :: complex A[N], B[N], C[N], D[N];
int main(){
	scanf("%d", &n);
	for (register int i = 0; i < n; ++i)
		scanf("%lf", a + i), A[i].re = a[i], B[i].re = i ? 1.0 / i / i : 0;
	Polynomial :: Multiply(n, A, n, B, C);
	memset(A, 0, sizeof A);
	memset(B, 0, sizeof B);
	for (register int i = 0; i < n; ++i)
		A[i].re = a[n - i - 1], B[i].re = i ? 1.0 / i / i : 0, A[i].im = B[i].im = 0;
	Polynomial :: Multiply(n, A, n, B, D);
	std :: reverse(D, D + n);
	for (register int i = 0; i < n; ++i)
		printf("%.3lf\n", (double)(C[i].re - D[i].re));
}
