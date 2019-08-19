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
char a[N << 1], b[N];
int n, m, nx[N << 1][26];
int main(){
	scanf("%s%s", a + 1, b + 1);
	n = strlen(a + 1), m = strlen(b + 1);
	for (register int i = 1; i <= n; ++i) a[n + i] = a[i];
	for (register int i = 0; i < 26; ++i) nx[n << 1][i] = -1;
	for (register int i = (n << 1) - 1; ~i; --i){
		for (register int j = 0; j < 26; ++j) nx[i][j] = nx[i + 1][j];
		nx[i][a[i + 1] - 'a'] = i % n + 1;
	}
	int k = 0, s = 0;
	for (register int i = 1; i <= m; ++i)
		if (~nx[k][b[i] - 'a']){
			if (nx[k][b[i] - 'a'] <= k) ++s;
			k = nx[k][b[i] - 'a'];
		}
		else return printf("-1\n"), 0;
	printf("%lld\n", 1ll * s * n + k);
}