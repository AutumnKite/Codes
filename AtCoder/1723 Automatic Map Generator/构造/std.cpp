#include <cstdio>
int n, m, t;
char a[105][105];
int main(){
	scanf("%d%d%d", &n, &m, &t);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			if (t && (i & 1) && (j & 1)) a[i][j] = '#', --t; else a[i][j] = '.';
	if (t) return printf("IMPOSSIBLE\n"), 0;
	for (register int i = 1; i <= n; ++i){
		for (register int j = 1; j <= m; ++j) putchar(a[i][j]);
		putchar('\n');
	}
}
