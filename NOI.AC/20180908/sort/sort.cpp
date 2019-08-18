#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	int x = 0;
	char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, a[50005];
int main(){
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i){
		register int k = i;
		for (register int j = i + 1; j <= n; ++j){
			a[j] < a[k] ? k = j : 0;
			if (a[k] == 0) break;
		}
		if (k != i) printf("%d %d\n", i, k), std :: reverse(a + i, a + k + 1);
	}
	printf("-1 -1\n");
}