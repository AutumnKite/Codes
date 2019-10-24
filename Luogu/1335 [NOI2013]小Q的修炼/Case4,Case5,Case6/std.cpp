#include <cstdio>
#include <cstring>
char s[100];
int q, n, m, nx[2005], w[2005], v[2005], id[12005];
int f[2005][10005], g[2005][10005];
void print_ans(int p, int k){
	if (p == 1) return;
	if (g[p][k] < 0){
		print_ans(-g[p][k], k);
		if (m - k >= w[-g[p][k]]) puts("2");
	}
	else{
		print_ans(g[p][k], k - w[g[p][k]]);
		puts("1");
	}
}
int main(){
	freopen("train.in", "r", stdin);
	freopen("train.out", "w", stdout);
	scanf("%d", &q), scanf("%s", s);
	for (register int i = 1; i <= q; ++i){
		scanf("%s", s);
		if (i == 1){ scanf("%s%s%s", s, s, s), scanf("%d", &m); continue; }
		if (s[0] == 'i'){ id[i] = n + 1, scanf("%s%s%s%s%s%s", s, s, s, s, s, s); continue; }
		++n, scanf("%s", s), scanf("%d", &nx[n]);
		if (nx[n] < 1 || nx[n] > q) nx[n] = 0;
		++i, scanf("%s%s%s%s", s, s, s, s), scanf("%d", &w[n]);
		++i, scanf("%s%s%s%s", s, s, s, s), scanf("%d", &v[n]);
	}
	id[0] = n + 1;
	for (register int i = 1; i <= n; ++i) nx[i] = id[nx[i]];
	memset(f, 0xc0, sizeof f);
	f[1][0] = 0;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 0; j <= m; ++j){
			if (f[i][j] > f[nx[i]][j])
				f[nx[i]][j] = f[i][j], g[nx[i]][j] = -i;
			if (j + w[i] > m) continue;
			if (f[i][j] + v[i] > f[i + 1][j + w[i]])
				f[i + 1][j + w[i]] = f[i][j] + v[i], g[i + 1][j + w[i]] = i;
		}
	int ans = -0x3f3f3f3f, k = 0;
	for (register int i = 0; i <= m; ++i)
		if (f[n + 1][i] > ans) ans = f[n + 1][i], k = i;
	print_ans(n + 1, k);
	fprintf(stderr, "%d\n", ans);
}
