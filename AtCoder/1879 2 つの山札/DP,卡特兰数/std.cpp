#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 1005
#define P 1000000007
int n, a[N], b[N], f[N][N], h[N];
int qpow(int a, int b = P - 2){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int add(int x, int y){
	return (x += y) >= P ? x - P : x;
}
int del(int x, int y){
	return (x -= y) < 0 ? x + P : x;
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i) b[i] = read();
	h[0] = 1;
	for (register int i = 1; i <= n; ++i)
		h[i] = 1ll * h[i - 1] * (4 * i - 2) % P * qpow(i + 1) % P;
	f[1][1] = 1;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n; ++j){
			if (i == 1 && j == 1) continue;
			f[i][j] = add(f[i - 1][j], f[i][j - 1]);
			if (a[i] == b[j]){
				int t = 0;
				for (register int k = 1; k < i && k < j; ++k)
					if (a[i - k] == b[j - k])
						f[i][j] = del(f[i][j], 1ll * f[i - k][j - k] * h[t] % P), ++t;
			}
		}
	printf("%d\n", f[n][n]);
}
