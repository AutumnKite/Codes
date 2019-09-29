#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <map>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, m, a[20][20], dp[20][1 << 20];
long long ans;
bool check(int p, int q){
	int cr = 0, r[20], cc = 0, c[20];
	for (register int i = 0; i < n; ++i)
		if (p >> i & 1) r[cr++] = i;
	for (register int i = 0; i < m; ++i)
		if (q >> i & 1) c[cc++] = i;
	for (register int i = 0; i < cr; ++i){
		bool flag0 = 1, flag1 = 1;
		for (register int j = 1; j < cc; ++j)
			flag0 &= a[r[i]][c[j - 1]] < a[r[i]][c[j]], flag1 &= a[r[i]][c[j - 1]] > a[r[i]][c[j]];
		if (!flag0 && !flag1) return 0;
	}
	for (register int j = 0; j < cc; ++j){
		bool flag0 = 1, flag1 = 1;
		for (register int i = 1; i < cr; ++i)
			flag0 &= a[r[i - 1]][c[j]] < a[r[i]][c[j]], flag1 &= a[r[i - 1]][c[j]] > a[r[i]][c[j]];
		if (!flag0 && !flag1) return 0;
	}
	return 1;
}
int main(){
	n = read(), m = read();
	for (register int i = 0; i < n; ++i)
		for (register int j = 0; j < m; ++j)
			a[i][j] = read();
	for (register int p = 1; p < (1 << n); ++p)
		for (register int q = 1; q < (1 << m); ++q)
			if (check(p, q)) ++ans;
	printf("%lld\n", ans);
}