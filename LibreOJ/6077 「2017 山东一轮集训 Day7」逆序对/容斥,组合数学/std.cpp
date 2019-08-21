#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
#define P 1000000007
int n, k, fac[N << 1], inv[N << 1], t, F[455][N], f[N], ans;
void inc(int &a, int b){
	(a += b) >= P ? a -= P : 0;
}
void dec(int &a, int b){
	(a -= b) < 0 ? a += P : 0;
}
int qpow(int a, int b = P - 2){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void init(int n, int k){
	fac[0] = 1;
	for (register int i = 1; i <= n + k; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n + k] = qpow(fac[n + k]);
	for (register int i = n + k; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
	t = std :: min(n, int(sqrt(2 * k)) + 1);
	F[0][0] = 1, f[0] = 1;
	for (register int i = 1; i <= t; ++i)
		for (register int j = i * (i + 1) >> 1; j <= k; ++j){
			dec(F[i][j], F[i - 1][j - i]), inc(F[i][j], F[i][j - i]);
			if (j >= n + 1) inc(F[i][j], F[i - 1][j - n - 1]);
			inc(f[j], F[i][j]);
		}
}
int C(int n, int m){
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}
int main(){
	n = read(), k = read();
	init(n, k);
	for (register int i = 0; i <= k; ++i) inc(ans, 1ll * f[i] * C(k - i + n - 1, n - 1) % P);
	printf("%d\n", ans);
}
