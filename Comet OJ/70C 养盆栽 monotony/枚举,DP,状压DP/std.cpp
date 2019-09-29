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
int n, m, a[20][20], dp[20][1 << 20], f[20][20];
long long ans;
bool check(int p, int x){
	int cnt = 0, r[20];
	for (register int i = 0; i < n; ++i)
		if (p >> i & 1) r[cnt++] = i;
	bool flag0 = 1, flag1 = 1;
	for (register int i = 1; i < cnt; ++i)
		flag0 &= a[r[i - 1]][x] < a[r[i]][x], flag1 &= a[r[i - 1]][x] > a[r[i]][x];
	return flag0 || flag1;
}
int main(){
	n = read(), m = read();
	for (register int i = 0; i < n; ++i)
		for (register int j = 0; j < m; ++j)
			a[i][j] = read();
	for (register int i = 0; i < m; ++i)
		for (register int j = 0; j < i; ++j)
			for (register int k = 0; k < n; ++k)
				f[i][j] |= (a[k][j] < a[k][i]) << k;
	for (register int p = 1; p < (1 << n); ++p){
		int cnt = 0, r[20];
		for (register int i = 0; i < m; ++i)
			if (check(p, i)) r[cnt++] = i;
		ans += cnt;
		for (register int i = 0; i < cnt; ++i)
			for (register int j = 0; j < i; ++j)
				dp[i][f[r[i]][r[j]] & p] += dp[j][f[r[i]][r[j]] & p] + 1, ans += dp[j][f[r[i]][r[j]] & p] + 1;
		for (register int i = 0; i < cnt; ++i)
			for (register int j = 0; j < i; ++j)
				dp[i][f[r[i]][r[j]] & p] = 0;
	}
	printf("%lld\n", ans);
}