#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
#define N 50005
int n, q, a[N], mx[N][20], mn[N][20], Log[N];
int main(){
	n = read(), q = read(), Log[1] = 0;
	for (register int i = 2; i <= n; ++i) Log[i] = Log[i >> 1] + 1;
	for (register int i = 1; i <= n; ++i)
		mx[i][0] = mn[i][0] = a[i] = read();
	for (register int j = 1; j <= 18; ++j)
		for (register int i = 1; i + (1 << j) - 1 <= n; ++i){
			mx[i][j] = std :: max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
			mn[i][j] = std :: min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
		}
	while (q--){
		int l = read(), r = read(), t = Log[r - l + 1], Mx, Mn;
		Mx = std :: max(mx[l][t], mx[r - (1 << t) + 1][t]);
		Mn = std :: min(mn[l][t], mn[r - (1 << t) + 1][t]);
		printf("%d\n", Mx - Mn);
	}
}
