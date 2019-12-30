#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(long long x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 100005;
int n, q, a[N], tp, sta[N];
long long f[N], sf[N], g[N], sg[N];
int mn[N][17], Log[N];
int my_min(int x, int y){
	return a[x] < a[y] ? x : y;
}
int query(int l, int r){
	int t = Log[r - l + 1];
	return my_min(mn[l][t], mn[r - (1 << t) + 1][t]);
}
int main(){
	n = read(), q = read();
	for (register int i = 1; i <= n; ++i) a[i] = read(), mn[i][0] = i;
	tp = 0, sta[0] = 0, f[0] = sf[0] = 0;
	for (register int i = 1; i <= n; ++i){
		f[i] = f[i - 1];
		while (tp && a[i] <= a[sta[tp]]) f[i] -= 1ll * (sta[tp] - sta[tp - 1]) * a[sta[tp]], --tp;
		sta[++tp] = i, f[i] += 1ll * (sta[tp] - sta[tp - 1]) * a[sta[tp]];
	}
	for (register int i = 1; i <= n; ++i) sf[i] = sf[i - 1] + f[i];
	tp = 0, sta[0] = n + 1, g[n + 1] = sg[n + 1] = 0;
	for (register int i = n; i; --i){
		g[i] = g[i + 1];
		while (tp && a[i] <= a[sta[tp]]) g[i] -= 1ll * (sta[tp - 1] - sta[tp]) * a[sta[tp]], --tp;
		sta[++tp] = i, g[i] += 1ll * (sta[tp - 1] - sta[tp]) * a[sta[tp]];
	}
	for (register int i = n; i; --i) sg[i] = sg[i + 1] + g[i];
	Log[1] = 0;
	for (register int i = 2; i <= n; ++i) Log[i] = Log[i >> 1] + 1;
	for (register int j = 1; j <= 16; ++j)
		for (register int i = 1; i <= n - (1 << j) + 1; ++i)
			mn[i][j] = my_min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
	while (q--){
		int l = read(), r = read(), p = query(l, r);
		print(1ll * a[p] * (p - l + 1) * (r - p + 1) + sf[r] - sf[p] - f[p] * (r - p) + sg[l] - sg[p] - g[p] * (p - l));
	}
}
