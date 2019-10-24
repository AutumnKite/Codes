#include <cstdio>
#include <cctype>
#include <algorithm>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int P = 2333;
int C[P][P], f[P][P];
long long n, k;
int add(int a, int b){
	return (a += b) >= P ? a - P : a;
}
int Lucas(long long n, long long m){
	if (n < m) return 0;
	if (n < P) return C[n][m];
	return 1ll * Lucas(n / P, m / P) * C[n % P][m % P] % P;
}
int F(long long n, long long k){
	if (k > n) k = n;
	if (n < P) return f[n][k];
	return (1ll * F(n / P, k / P - 1) * F(n % P, P - 1) + 1ll * Lucas(n / P, k / P) * F(n % P, k % P)) % P;
}
int main(){
	for (register int i = 0; i < P; ++i){
		C[i][0] = C[i][i] = f[i][0] = 1;
		for (register int j = 1; j < i; ++j)
			C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]), f[i][j] = add(f[i][j - 1], C[i][j]);
		if (i) f[i][i] = add(f[i][i - 1], 1);
	}
	int T = read();
	while (T--){
		n = read(), k = read();
		printf("%d\n", F(n, k));
	}
}