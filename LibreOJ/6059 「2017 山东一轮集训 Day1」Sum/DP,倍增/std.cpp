#include <cstdio>
#include <cstring>
#define P 998244353
int n, p, m, pw[35], dp[35][55][55], s[55][55], s1[55][55];
void upd(int &x, int y){
	(x += y) >= P ? x -= P : 0;
}
int add(int x, int y){
	return (x += y) >= P ? x - P : x;
}
int del(int x, int y){
	return (x -= y) < 0 ? x + P : x;
}
int mul(int x, int y){
	return 1ll * x * y % P;
}
int qpow(int a, int b = P - 2, int p = P){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % p) if (b & 1) s = 1ll * s * a % p;
	return s;
}
int main(){
	scanf("%d%d%d", &n, &p, &m);
	for (register int i = 0; i <= 9; ++i) ++dp[0][i % p][i];
	pw[0] = 1;
	for (register int i = 1; i <= 30; ++i) pw[i] = pw[i - 1] << 1;
	for (register int i = 0; i <= 30; ++i) pw[i] = qpow(10, pw[i], p);
	for (register int i = 0; i < 30; ++i)
		for (register int j1 = 0; j1 < p; ++j1)
			for (register int j2 = 0; j2 < p; ++j2)
				for (register int k1 = 0; k1 <= m; ++k1)
					for (register int k2 = 0; k2 <= m - k1; ++k2)
						upd(dp[i + 1][(1ll * j1 * pw[i] + j2) % p][k1 + k2], mul(dp[i][j1][k1], dp[i][j2][k2]));
	s[0][0] = 1;
	for (register int i = 30; ~i; --i)
		if ((1 << i) <= n){
			memcpy(s1, s, sizeof s1), memset(s, 0, sizeof s);
			for (register int j1 = 0; j1 < p; ++j1)
				for (register int j2 = 0; j2 < p; ++j2)
					for (register int k1 = 0; k1 <= m; ++k1)
						for (register int k2 = 0; k2 <= m - k1; ++k2)
							upd(s[(1ll * j1 * pw[i] + j2) % p][k1 + k2], mul(s1[j1][k1], dp[i][j2][k2]));
			n -= (1 << i);
		}
	for (register int i = 1; i <= m; ++i) upd(s[0][i], s[0][i - 1]);
	for (register int i = 0; i <= m; ++i) printf("%d ", s[0][i]);
}
