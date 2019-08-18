#include <cstdio>
#include <algorithm>
#define N 70005
#define P 998244353
int n, p, m, pw[35], dp[35][N], s[N], tmp[N], len;
void upd(int &x, int y){
	(x += y) >= P ? x -= P : 0;
}
int add(int x, int y){
	return (x += y) >= P ? x - P : x;
}
int del(int x, int y){
	return (x -= y) < 0 ? x + P : x;
}
int qpow(int a, int b = P - 2, int p = P){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % p) if (b & 1) s = 1ll * s * a % p;
	return s;
}
struct Number_Theory_Transform{
	int n, rev[N], omega[N];
	void init(int m){
		n = m;
		register int k = 0;
		while ((1 << k) < n) ++k;
		for (register int i = 1; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k >> 1;
	}
	void NTT(int* a, int o){
		for (register int i = 0; i < n; ++i) i < rev[i] ? std :: swap(a[i], a[rev[i]]), 0 : 0;
		for (register int m = 1; m < n; m <<= 1){
			register int l = m << 1, omega1 = qpow(o == 1 ? 3 : 332748118, (P - 1) / l);
			omega[0] = 1;
			for (register int i = 1; i < m; ++i) omega[i] = 1ll * omega[i - 1] * omega1 % P;
			for (register int* p = a; p < a + n; p += l)
				for (register int i = 0; i < m; ++i){
					register int t = 1ll * omega[i] * p[m + i] % P;
					p[m + i] = del(p[i], t), upd(p[i], t);
				}
		}
		if (o == -1){
			register int _n = qpow(n);
			for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * _n % P;
		}
	}
}T;
void multiply(int na, int *A, int nb, int *B, int *C){
	int n;
	if (na <= 20 && nb <= 20){
		n = std :: max(na, nb);
		for (register int i = 0; i < n; ++i) C[i] = 0;
		for (register int i = 0; i < na; ++i)
			for (register int j = 0; j < nb; ++j)
				if (i + j < n) upd(C[i + j], 1ll * A[i] * B[j] % P);
		return;
	}
	int a[N], b[N];
	n = 1;
	while (n < na + nb - 1) n <<= 1;
	for (register int i = 0; i < na; ++i) a[i] = A[i];
	for (register int i = 0; i < nb; ++i) b[i] = B[i];
	for (register int i = na; i < n; ++i) a[i] = 0;
	for (register int i = nb; i < n; ++i) b[i] = 0;
	T.init(n), T.NTT(a, 1), T.NTT(b, 1);
	for (register int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
	T.NTT(a, -1);
	for (register int i = 0; i < std :: max(na, nb); ++i) C[i] = a[i];
}
int main(){
	scanf("%d%d%d", &n, &p, &m);
	len = (m + 1) * p * 2;
	for (register int i = 0; i <= 9 && i <= m; ++i) ++dp[0][i * p * 2 + i % p];
	pw[0] = 1;
	for (register int i = 1; i <= 30; ++i) pw[i] = pw[i - 1] << 1;
	for (register int i = 0; i <= 30; ++i) pw[i] = qpow(10, pw[i], p);
	for (register int i = 0; i < 30; ++i){
		for (register int j = 0; j < len; ++j) tmp[j] = 0;
		for (register int j = 0; j <= m; ++j)
			for (register int k = 0; k < p; ++k)
				upd(tmp[j * p * 2 + 1ll * k * pw[i] % p], dp[i][j * p * 2 + k]);
		multiply(len, tmp, len, dp[i], dp[i + 1]);
		for (register int j = 0; j <= m; ++j)
			for (register int k = 0; k < p; ++k)
				upd(dp[i + 1][j * p * 2 + k], dp[i + 1][j * p * 2 + k + p]), dp[i + 1][j * p * 2 + k + p] = 0;
	}
	s[0] = 1;
	for (register int i = 30; ~i; --i)
		if ((1 << i) <= n){
			for (register int j = 0; j < len; ++j) tmp[j] = 0;
			for (register int j = 0; j <= m; ++j)
				for (register int k = 0; k < p; ++k)
					upd(tmp[j * p * 2 + 1ll * k * pw[i] % p], s[j * p * 2 + k]), s[j * p * 2 + k] = 0;
			multiply(len, tmp, len, dp[i], s);
			for (register int j = 0; j <= m; ++j)
				for (register int k = 0; k < p; ++k)
					upd(s[j * p * 2 + k], s[j * p * 2 + k + p]), s[j * p * 2 + k + p] = 0;
			n -= (1 << i);
		}
	int sum = 0;
	for (register int i = 0; i <= m; ++i) upd(sum, s[i * p * 2]), printf("%d ", sum);
}
