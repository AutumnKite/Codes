#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int n, m, c, a[6][105];
int main(){
	freopen("test.in", "w", stdout);
	srand(time(0));
	scanf("%d%d%d", &n, &m, &c);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			a[i][j] = rand() % std :: min(c, 3);
	for (register int t = rand() % 5, i, j; t; --t)
		i = rand() % n + 1, j = rand() % m + 1, a[i][j] = rand() % c;
	printf("%d %d\n", n, m);
	for (register int i = 1; i <= n; ++i){
		for (register int j = 1; j <= m; ++j) printf("%d ", a[i][j]);
		putchar('\n');
	}
}