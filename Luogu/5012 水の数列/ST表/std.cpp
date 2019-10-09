#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 1000005
int n, q, m, a[N], len[N], Log[N >> 1], st[N >> 1][20], cnt, mx;
std :: vector<int> pos[N];
long long s, sum[N];
void add(int x){
	s -= 1ll * len[x - 1] * len[x - 1] + 1ll * len[x + 1] * len[x + 1];
	len[x] = len[x - 1] + len[x + 1] + 1, s += 1ll * len[x] * len[x];
	len[x - len[x - 1]] = len[x + len[x + 1]] = len[x];
	if (len[x - 1] && len[x + 1]) --cnt;
	else if (!len[x - 1] && !len[x + 1]) ++cnt;
}
int my_max(int x, int y){
	if (x > y) std :: swap(x, y);
	return x && sum[x] * y > sum[y] * x ? x : y;
}
int main(){
	n = read(), q = read();
	for (register int i = 1; i <= n; ++i)
		a[i] = read(), m = std :: max(m, a[i]), pos[a[i]].push_back(i);
	for (register int i = 1; i <= m; ++i){
		for (register int j = 0; j < pos[i].size(); ++j) add(pos[i][j]);
		sum[i] = s, st[cnt][0] = my_max(st[cnt][0], i), mx = std :: max(mx, cnt);
	}
	Log[1] = 0;
	for (register int i = 2; i <= mx; ++i) Log[i] = Log[i >> 1] + 1;
	for (register int j = 1; j <= 19; ++j)
		for (register int i = 1; i + (1 << j) - 1 <= mx; ++i)
			st[i][j] = my_max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	int lastans = 0;
	while (q--){
		int a = read() % n, b = read() % n, x = read() % n, y = read() % n, l, r, R, t, ansx;
		l = (1ll * a * lastans % n + x - 1 + 2 * n) % n + 1;
		r = (1ll * b * lastans % n + y - 1 + 2 * n) % n + 1;
		if (l > r) std :: swap(l, r);
		R = r;
		if (r > mx) r = mx;
		if (l > mx) ansx = 0;
		else t = Log[r - l + 1], ansx = my_max(st[l][t], st[r - (1 << t) + 1][t]);
		if (!ansx) printf("-1 -1\n%d %d %d\n", l, R, lastans), lastans = 1;
		else printf("%lld %d\n%d %d %d\n", sum[ansx], ansx, l, R, lastans), lastans = sum[ansx] * ansx % n;
	}
}
