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
#define N 1005
#define P 10000
int n, k, C[N << 1][N << 1], t, F[55][N], f[N], ans;
void inc(int &a, int b){
	(a += b) >= P ? a -= P : 0;
}
void dec(int &a, int b){
	(a -= b) < 0 ? a += P : 0;
}
void init(int n, int k){
	for (register int i = 0; i <= n + k; ++i){
		C[i][0] = C[i][i] = 1;
		for (register int j = 1; j < i; ++j)
			C[i][j] = C[i - 1][j - 1], inc(C[i][j], C[i - 1][j]);
	}
	t = std :: min(n, int(sqrt(2 * k)) + 1);
	F[0][0] = 1, f[0] = 1;
	for (register int i = 1; i <= t; ++i)
		for (register int j = i * (i + 1) >> 1; j <= k; ++j){
			dec(F[i][j], F[i - 1][j - i]), inc(F[i][j], F[i][j - i]);
			if (j >= n + 1) inc(F[i][j], F[i - 1][j - n - 1]);
			inc(f[j], F[i][j]);
		}
}
int main(){
	n = read(), k = read();
	init(n, k);
	for (register int i = 0; i <= k; ++i) inc(ans, 1ll * f[i] * C[k - i + n - 1][n - 1] % P);
	printf("%d\n", ans);
}
