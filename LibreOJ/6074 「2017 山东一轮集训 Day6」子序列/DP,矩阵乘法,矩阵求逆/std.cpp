#include <cstdio>
#include <cctype>
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
int n, q, a[10][10], av[10][10], f[N][10], fv[N][10];
char s[N];
int plus(int a, int b){
	return (a += b) >= P ? a - P : a;
}
int minus(int a, int b){
	return (a -= b) < 0 ? a + P : a;
}
void init(int n){
	for (register int i = 0; i <= 9; ++i)
		a[i][i] = av[i][i] = f[0][i] = 1;
	for (register int i = 1; i <= n; ++i){
		int t = s[i] - 'a';
		for (register int j = 0; j <= 9; ++j){
			f[i][j] = plus(minus(f[i - 1][j], a[j][t]), f[i - 1][j]);
			a[j][t] = f[i - 1][j];
			fv[i][j] = av[t][j];
			av[t][j] = minus(plus(av[t][j], av[t][j]), fv[i - 1][j]);
		}
	}
	for (register int i = 0; i <= n; ++i)
		for (register int j = 0; j <= 9; ++j)
			fv[i][j] = minus(j == 9, fv[i][j]);
}
int main(){
	while (islower(s[++n] = getchar())) ;
	--n;
	init(n);
	q = read();
	while (q--){
		int l = read(), r = read(), ans = 0;
		for (register int i = 0; i <= 9; ++i)
			ans = plus(ans, 1ll * fv[l - 1][i] * f[r][i] % P);
		printf("%d\n", minus(ans, 1));
	}
}
