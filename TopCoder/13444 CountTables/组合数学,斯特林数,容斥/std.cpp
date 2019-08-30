#include <cstdio>
#include <algorithm>
#define N 4005
#define P 1000000007
int n, m, c, fac[N], inv[N], S[N][N], dp[N];
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int add(int x, int y){
	return (x += y) >= P ? x -= P : x;
}
int sub(int x, int y){
	return (x -= y) < 0 ? x += P : x;
}
struct CountTables{
	int howMany(int _n, int _m, int _c){
		n = _n, m = _m, c = _c;
		S[0][0] = 1;
		for (register int i = 1; i <= m; ++i)
			for (register int j = 1; j <= i; ++j)
				S[i][j] = add(S[i - 1][j - 1], 1ll * j * S[i - 1][j] % P);
		for (register int i = 1, pw = 1; i <= m; ++i){
			pw = 1ll * pw * c % P;
			dp[i] = 1;
			for (register int j = 1; j <= n; ++j) dp[i] = 1ll * dp[i] * (pw - j + 1 + P) % P;
			for (register int j = 1; j < i; ++j) dp[i] = sub(dp[i], 1ll * S[i][j] * dp[j] % P);
		}
		return dp[m];
	}
}T;
int main(){
	printf("%d\n", T.howMany(2, 3, 5));
}